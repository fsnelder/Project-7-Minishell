/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 15:17:55 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/08 11:28:38 by fsnelder      ########   odam.nl         */
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

// function finds the command based on the PATH variable
// if a '/' does not appear
static int	find_command(char **out_path, char *name)
{
	*out_path = name;
	if (ft_strchr(name, '/'))
		return (SUCCESS);
	// TODO: search in PATH
	return (SUCCESS);
}

int	set_redirect(t_redirect *redirect, int file_mode, int dup_to)
{
	int	fd;

	fd = open(redirect->expanded, file_mode,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
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

static int	handle_child_process(t_executor *executor, t_command *command)
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
	execve(args[0], args, environ);
	return (GENERAL_ERROR);
}

static int	execute_one(t_executor *executor, int index, t_command *command)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exit(handle_child_process(executor, command));
	else if (pid < 0)
		return (GENERAL_ERROR);
	executor->pids[index] = pid;
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
		abort();
		// return (execute_pipe_sequence(commands));
	if (result != SUCCESS)
		return (result);
	executor_wait(&executor);
	return (result);
}
