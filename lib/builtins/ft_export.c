/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_export.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 09:45:09 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/12 15:31:01 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "builtins.h"
#include "environment.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// TODO: sorted output

static void	sorted_output(t_environment *env)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < env->len)
	{
		j = 0;
		while (j < env->len)
		{
			if (ft_strncmp(env->envp[i], env->envp[j], INT_MAX) < 0)
			{
				temp = env->envp[i];
				env->envp[i] = env->envp[j];
				env->envp[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	shallow_copy_env(t_environment *env)
{
	env->len = g_ms_data.env.len;
	env->cap = g_ms_data.env.cap;
	env->envp = (char **)ft_malloc((env->len + 1) * sizeof(char *));
	ft_memcpy(env->envp, g_ms_data.env.envp, (env->len + 1) * sizeof(char *));
}

static int	export_no_arguments(const char **args, const char **envp)
{
	t_environment	env;
	size_t			i;

	shallow_copy_env(&env);
	sorted_output(&env);
	i = 0;
	while (i < env.len)
	{
		printf("%s\n", env.envp[i]);
		i++;
	}
	free(env.envp);
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
