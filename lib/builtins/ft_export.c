/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 09:45:09 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 13:02:23 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "builtins.h"
#include "environment.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: sorted output

static void sorted_output (const char **args, const char **envp)
{
	char	*temp;
	int		i;
	abort();
}

static int	export_no_arguments(const char **args, const char **envp)
{
	ft_env(args, envp);
	return (SUCCESS);
}

static int	export_argument(t_environment *env, const char *arg)
{
	char	*assignment;

	assignment = ft_strchr(arg, '=');
	if (assignment == NULL)
		return (SUCCESS);
	*assignment = '\0';
	if (!is_valid_identifier(arg))
	{
		*assignment = '=';
		printf("export: `%s': not a valid identifier\n", arg);
		return (GENERAL_ERROR);
	}
	environment_set(env, arg, &assignment[1]);
	return (SUCCESS);
}

// a=b -> "a\0" -> "a\0b\0"
int	ft_export(const char **args, const char **envp)
{
	t_environment	*env;
	int				result;

	args++;
	env = &g_ms_data.env;
	if (*args == NULL)
		return (export_no_arguments(args, envp));
	result = SUCCESS;
	while (*args)
	{
		if (export_argument(env, *args) != SUCCESS)
			result = GENERAL_ERROR;
		args++;
	}
	return (result);
}
