/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 09:44:59 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/12 15:35:38 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "environment.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void	update_environment(const char *newpwd)
{
	t_environment	*env;
	const char		*oldpwd;

	if (!newpwd)
		return ;
	env = &g_ms_data.env;
	oldpwd = environment_get(env, "PWD");
	if (oldpwd)
		environment_set(env, "OLDPWD", oldpwd);
	environment_set(env, "PWD", newpwd);
	free((void *)newpwd);
}

int	ft_cd(const char **args, const char **envp)
{
	args++;
	if (*args == NULL)
	{
		printf("cd without arguments not supported\n");
		return (1);
	}
	if (chdir(*args) != 0)
	{
		perror("cd");
		return (GENERAL_ERROR);
	}
	update_environment(getcwd(NULL, 0));
	return (SUCCESS);
}
