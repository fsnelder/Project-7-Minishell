/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_std.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/12 11:56:45 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/12 13:27:25 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"
#include "parser.h"
#include "builtins.h"
#include "expand.h"
#include <stdbool.h>
#include "util.h"
#include <stdio.h>
#include <unistd.h>

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
