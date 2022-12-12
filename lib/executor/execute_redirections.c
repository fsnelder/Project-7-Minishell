/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_redirections.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/12 11:28:22 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/12 16:04:19 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "executor_utils.h"
#include "builtins.h"
#include <fcntl.h>
#include <unistd.h>

int	set_redirect(t_redirect *redirect, int file_mode, int dup_to)
{
	int	fd;

	fd = open(redirect->expanded, file_mode,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		perror(redirect->expanded);
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
		return (set_redirect(redirect,
				O_APPEND | O_CREAT | O_WRONLY, STDOUT_FILENO));
	return (GENERAL_ERROR);
}

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
