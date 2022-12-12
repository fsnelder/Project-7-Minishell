/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 15:17:55 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/12 15:42:40 by fsnelder      ########   odam.nl         */
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
	executor_wait(&executor);
	if (result != SUCCESS)
		executor.code = result;
	update_exitcode(executor.code);
	executor_destroy(&executor);
	return (result);
}
