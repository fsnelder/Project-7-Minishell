/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 15:17:55 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/08 13:49:01 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"
#include "expand.h"
#include "util.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

static void	executor_init(t_executor *executor, t_list *commands)
{
	executor->ncommands = ft_lstsize(commands);
	executor->commands = commands;
	executor->pids = (int *)ft_malloc(executor->ncommands * sizeof(int));
	ft_memset(executor->pids, -1, sizeof(int) * executor->ncommands);
}

static void	executor_destroy(t_executor *executor)
{
	free(executor->pids);
}

static void	executor_wait(t_executor *executor)
{
	int	i;

	i = 0;
	while (i < (int)executor->ncommands)
	{
		if (executor->pids[i] == -1)
			break ;
		// TODO: error handling and exit code
		waitpid(executor->pids[i], NULL, 0);
		i++;
	}
}

void	*token_to_expand(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	return (expand_token(token, (const char **)environ));
}

void	expand_redirection(void *ptr)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)ptr;
	redirect->expanded = expand_token(redirect->word, (const char **)environ);
}

static char	*construct_full_path(const char *directory, const char *name)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(directory, "/");
	full_path = ft_strjoin(temp, name);
	free(temp);
	return (full_path);
}

static char	*search_path(const char *path, const char *name)
{
	char	**paths;
	int		i;
	char	*full_path;

	paths = ft_split(path, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		full_path = construct_full_path(paths[i], name);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

// function finds the command based on the PATH variable
// if a '/' does not appear
static int	find_command(char **out_path, char *name)
{
	const char	*path;

	*out_path = name;
	if (ft_strchr(name, '/'))
		return (SUCCESS);
	// TODO: search in PATH
	path = getenv("PATH");
	if (!path)
		return (COMMAND_NOT_FOUND);
	*out_path = search_path(path, name);
	if (!*out_path)
		return (COMMAND_NOT_FOUND);
	return (SUCCESS);
}

int	set_redirect(t_redirect *redirect, int file_mode, int dup_to)
{
	int	fd;

	fd = open(redirect->expanded, file_mode,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		// TODO: use filename for error message
		perror("minishell: open");
		return (GENERAL_ERROR);
	}
	if (dup2(fd, dup_to) < 0)
	{
		perror("minishell: dup2");
		return (GENERAL_ERROR);
	}
	close(fd);
	return (SUCCESS);
}

int	set_redirection(t_redirect *redirect)
{
	int	fd;

	if (redirect->redirect_type == REDIRECT_IN)
		return (set_redirect(redirect, O_RDONLY, STDIN_FILENO));
	else if (redirect->redirect_type == REDIRECT_HEREDOC)
		return (set_redirect(redirect, O_RDONLY, STDIN_FILENO));
	else if (redirect->redirect_type == REDIRECT_OUT)
		return (set_redirect(redirect,
				O_WRONLY | O_TRUNC | O_CREAT, STDOUT_FILENO));
	else if (redirect->redirect_type == REDIRECT_APPEND)
		return (set_redirect(redirect, O_APPEND | O_CREAT, STDOUT_FILENO));
	return (GENERAL_ERROR);
}

// dup, dup2
// close unclosed FDs
int	set_redirections(t_list *redirections)
{
	int	result;

	while (redirections)
	{
		result = set_redirection((t_redirect *)redirections->content);
		if (result != SUCCESS)
			return (result);
		redirections = redirections->next;
	}
	return (SUCCESS);
}

char	**list_arguments_to_array(t_list *arguments)
{
	size_t	size;
	char	**result;
	int		i;

	size = ft_lstsize(arguments);
	result = ft_malloc((size + 1) * sizeof(char *));
	result[size] = NULL;
	i = 0;
	while (arguments)
	{
		result[i] = (char *)arguments->content;
		i++;
		arguments = arguments->next;
	}
	return (result);
}

/*
1. expand command name, all arguments and all redirect names
2. find the command to execute using environment's PATH (unless command contains '/')
3. set redirections using dup, dup2
4. close other unclosed file descriptors
5. execute the command
*/

static int	handle_child_process(t_command *command)
{
	t_list	*expanded_arguments;
	int		result;
	char	**args;
	char	*full_path;

	ft_lstiter(command->redirections, expand_redirection);
	expanded_arguments = ft_lstmap(command->arguments, token_to_expand, free);
	if (expanded_arguments == NULL)
		return (SUCCESS);
	result = find_command(&full_path, (char *)expanded_arguments->content);
	if (result != SUCCESS)
		return (result);
	if (set_redirections(command->redirections) != SUCCESS)
		return (GENERAL_ERROR);
	args = list_arguments_to_array(expanded_arguments);
	execve(full_path, args, environ);
	perror("minishell");
	return (GENERAL_ERROR);
}

static int	execute_one(t_executor *executor, int index, t_command *command)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exit(handle_child_process(command));
	else if (pid < 0)
		return (GENERAL_ERROR);
	executor->pids[index] = pid;
	return (SUCCESS);
}

static int execute_piped_child(int std_in, int std_out, t_command *command)
{
	if (std_in != -1)
		dup2(std_in, STDIN_FILENO);
	if (std_out != -1)
		dup2(std_out, STDOUT_FILENO);
	close(std_in);
	close(std_out);
	exit(handle_child_process(command));
}

typedef struct s_command_info
{
	int			std_in;
	int			std_out;
	t_command	*command;
}	t_command_info;

static t_command_info	make_command_info(
	int std_in, int std_out, t_command *command)
{
	return ((t_command_info){std_in, std_out, command});
}

// 1. fork
// 2. redirect STDIN (if not first process)
// 3. redirect STDOUT (if not last process)
static int	execute_piped_command(
	t_executor *executor, int index, t_command_info info)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exit(execute_piped_child(info.std_in, info.std_out, info.command));
	else if (pid < 0)
		return (GENERAL_ERROR);
	executor->pids[index] = pid;
	close(info.std_in);
	close(info.std_out);
	return (SUCCESS);
}

static int	execute_pipe_sequence(t_executor *executor, t_list *commands)
{
	int					fds[2];
	int					previous_fd;
	int					index;

	index = 0;
	previous_fd = -1;
	while (commands)
	{
		if (commands->next == NULL)
			return (execute_piped_command(
					executor, index, make_command_info(
						previous_fd, -1, (t_command *)commands->content)));
		if (pipe(fds) < 0)
			return (GENERAL_ERROR);
		if (execute_piped_command(
				executor, index, make_command_info(previous_fd, fds[1],
					(t_command *)commands->content)) != SUCCESS)
			return (GENERAL_ERROR);
		previous_fd = fds[0];
		index++;
		commands = commands->next;
	}
	return (SUCCESS);
}

int	execute(t_list *commands)
{
	t_executor	executor;
	int			result;

	// TODO: handle all heredoc redirections and convert to a simple input file redirection
	executor_init(&executor, commands);
	if (executor.ncommands == 1)
		result = execute_one(&executor, 0, (t_command *)commands->content);
	else
		result = execute_pipe_sequence(&executor, commands);
	// TODO: reconsider: kill other child processes if a system call error occurs?
	executor_wait(&executor);
	executor_destroy(&executor);
	return (result);
}
