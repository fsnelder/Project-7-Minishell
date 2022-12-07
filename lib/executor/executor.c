/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsnelder <fsnelder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:17:55 by fsnelder          #+#    #+#             */
/*   Updated: 2022/12/07 15:42:48 by fsnelder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"
#include "util.h"
#include <stdio.h>
#include <unistd.h>

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

/*
1. expand command name, all arguments and all redirect names
2. find the command to execute using environment's PATH (unless command contains '/')
3. set redirections using dup, dup2
4. close other unclosed file descriptors
5. execute the command
*/

static int	handle_child_process(t_executor *executor, t_command *command)
{
	return (SUCCESS);
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

	// TODO: handle all heredoc redirections and convert to a simple input file redirection
	executor_init(&executor, commands);
	if (executor.ncommands == 1)
		return (execute_one(&executor, 0, (t_command *)commands->content));
	else
		abort();
		// return (execute_pipe_sequence(commands));
}
