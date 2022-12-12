/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pipe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 15:45:04 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/12 11:57:47 by fsnelder      ########   odam.nl         */
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

int	execute_piped_command(
	t_executor *executor, t_command_info *info)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exit(execute_piped_child(info));
	else if (pid < 0)
		return (GENERAL_ERROR);
	executor->pids[info->pid_index] = pid;
	return (free_fds_and_return(SUCCESS, 2, info->input_fd, info->piped[1]));
}

int	execute_pipe_sequence(t_executor *executor, t_list *commands)
{
	t_command_info		cinfo;

	init_command_info(&cinfo);
	while (commands)
	{
		ft_memset(cinfo.piped, -1, 2 * sizeof(int));
		cinfo.command = (t_command *)commands->content;
		if (commands->next == NULL)
			return (execute_piped_command(executor, &cinfo));
		if (pipe(cinfo.piped) < 0)
			return (GENERAL_ERROR);
		if (execute_piped_command(executor, &cinfo) != SUCCESS)
			return (free_fds_and_return(GENERAL_ERROR, 3,
					cinfo.input_fd, cinfo.piped[0], cinfo.piped[1]));
		cinfo.input_fd = cinfo.piped[0];
		cinfo.pid_index++;
		commands = commands->next;
	}
	return (SUCCESS);
}

int	handle_child_process(t_command *command)
{
	int		result;
	char	*full_path;

	if (set_redirections(command->redirections) != SUCCESS)
		return (GENERAL_ERROR);
	if (command->argv[0] == NULL)
		return (SUCCESS);
	if (is_builtin(command->argv[0]))
		return (dispatch_builtin(command, command->argv));
	result = find_command(&full_path, command->argv[0]);
	if (result != SUCCESS)
	{
		printf("minishell: %s: command not found\n", command->argv[0]);
		return (result);
	}
	execve(full_path, command->argv, environ);
	perror("minishell");
	free(full_path);
	return (COMMAND_NOT_EXECUTABLE);
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

int	execute_piped_child(t_command_info *cinfo)
{
	if (set_pipe_redirections(cinfo->input_fd, cinfo->piped[1]) != SUCCESS)
		return (GENERAL_ERROR);
	if (cinfo->piped[0] != -1)
		close(cinfo->piped[0]);
	return (handle_child_process(cinfo->command));
}
