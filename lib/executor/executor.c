/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 15:17:55 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 15:55:39 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "executor_utils.h"
#include "parser.h"
#include "builtins.h"
#include "expand.h"
#include <stdbool.h>
#include "util.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <limits.h>

static void	executor_init(t_executor *executor, t_list *commands)
{
	executor->ncommands = ft_lstsize(commands);
	executor->commands = commands;
	executor->pids = (int *)ft_malloc(executor->ncommands * sizeof(int));
	ft_memset(executor->pids, -1, sizeof(int) * executor->ncommands);
	executor->code = 0;
}

static void	executor_destroy(t_executor *executor)
{
	free(executor->pids);
}

static void	executor_wait(t_executor *executor)
{
	int	i;
	int	status;

	i = 0;
	while (i < (int)executor->ncommands)
	{
		if (executor->pids[i] == -1)
			break ;
		if (waitpid(executor->pids[i], &status, 0) < 0)
			perror("waitpid");
		if (WIFEXITED(status))
			executor->code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			executor->code = SIGNAL_CODE + WTERMSIG(status);
		i++;
	}
}

char	*construct_full_path(const char *directory, const char *name)
{
	char	*temp;
	char	*full_path;

	temp = malloc_check(ft_strjoin(directory, "/"));
	full_path = malloc_check(ft_strjoin(temp, name));
	free(temp);
	return (full_path);
}

char	*search_path(const char *path, const char *name)
{
	char	**paths;
	int		i;
	char	*full_path;

	paths = malloc_check(ft_split(path, ':'));
	i = 0;
	while (paths[i] != NULL)
	{
		full_path = construct_full_path(paths[i], name);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

// function finds the command based on the PATH variable
// if a '/' does not appear
int	find_command(char **out_path, char *name)
{
	const char	*path;

	*out_path = name;
	if (ft_strchr(name, '/'))
		return (SUCCESS);
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
	int	result;

	if (redirect->redirect_type == REDIRECT_IN)
		return (set_redirect(redirect, O_RDONLY, STDIN_FILENO));
	else if (redirect->redirect_type == REDIRECT_HEREDOC)
	{
		result = set_redirect(redirect, O_RDONLY, STDIN_FILENO);
		unlink(redirect->expanded);
		return (result);
	}
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

/*
1. expand command name, all arguments and all redirect names
2. check if the command is a builtin
3. find the command to execute using environment's PATH (unless command contains '/')
4. set redirections using dup, dup2
5. close other unclosed file descriptors
6. execute the command
*/

int	dup_std(int *std)
{
	std[0] = dup(STDIN_FILENO);
	if (std[0] == -1)
		return (GENERAL_ERROR);
	std[1] = dup(STDOUT_FILENO);
	if (std[1] == -1)
	{
		close(std[0]);
		return (GENERAL_ERROR);
	}
	return (SUCCESS);
}

// this function succeeding is essential for the program to continue
// so we exit on dup2 failure
int	reset_std(int *std)
{
	if (dup2(std[0], STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
	if (dup2(std[1], STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
	return (free_fds_and_return(SUCCESS, 2, std[0], std[1]));
}

int	builtin_main_process(
		t_executor *executor, t_command *command)
{
	int		code;
	int		std[2];

	if (dup_std(std) != SUCCESS)
		return (GENERAL_ERROR);
	if (set_redirections(command->redirections) != SUCCESS)
	{
		reset_std(std);
		return (GENERAL_ERROR);
	}
	executor->code = dispatch_builtin(command, command->argv);
	reset_std(std);
	return (SUCCESS);
}

// don't fork if builtin
// expand before fork for builtin check, move expansion from handle_child_process
int	execute_one(t_executor *executor, t_command *command)
{
	int		pid;

	if (is_builtin(command->argv[0]))
		return (builtin_main_process(executor, command));
	pid = fork();
	if (pid == 0)
		exit(handle_child_process(command));
	else if (pid < 0)
		return (GENERAL_ERROR);
	executor->pids[0] = pid;
	return (SUCCESS);
}

int	set_pipe_redirections(int input, int output)
{
	int	result;

	result = SUCCESS;
	if (input != -1)
	{
		if (dup2(input, STDIN_FILENO) < 0)
			result = (GENERAL_ERROR);
	}
	if (output != -1)
	{
		if (dup2(output, STDOUT_FILENO) < 0)
			result = GENERAL_ERROR;
	}
	return (free_fds_and_return(result, 2, input, output));
}

int execute_piped_child(t_command_info *cinfo)
{
	if (set_pipe_redirections(cinfo->input_fd, cinfo->piped[1]) != SUCCESS)
		return (GENERAL_ERROR);
	if (cinfo->piped[0] != -1)
		close(cinfo->piped[0]);
	return (handle_child_process(cinfo->command));
}

void	init_command_info(t_command_info *cinfo)
{
	cinfo->input_fd = -1;
	cinfo->pid_index = 0;
	cinfo->command = NULL;
	ft_memset(cinfo->piped, -1, 2 * sizeof(int));
}

int	execute(t_list *commands)
{
	t_executor	executor;
	int			result;

	if (process_heredocs(commands) != SUCCESS)
		return (GENERAL_ERROR);
	executor_init(&executor, commands);
	if (executor.ncommands == 1)
		result = execute_one(&executor, (t_command *)commands->content);
	else
		result = execute_pipe_sequence(&executor, commands);
	// TODO: reconsider: kill other child processes if a system call error occurs?
	executor_wait(&executor);
	if (result != SUCCESS)
		executor.code = result;
	update_exitcode(executor.code);
	executor_destroy(&executor);
	return (result);
}
