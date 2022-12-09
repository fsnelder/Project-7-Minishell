/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 11:08:08 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 11:33:11 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "environment_utils.h"
#include "util.h"
#include "libft.h"

t_environment	environment_init(const char **envp)
{
	t_environment	env;
	int				i;

	i = 0;
	while (envp[i])
		i++;
	env.envp = ft_malloc((i + 1) * sizeof(char *));
	env.cap = i + 1;
	env.len = i;
	env.envp[i] = NULL;
	i = 0;
	while (envp[i])
	{
		env.envp[i] = malloc_check(ft_strdup(envp[i]));
		i++;
	}
	environ = env.envp;
	return (env);
}

void	environment_destroy(t_environment *env)
{
	int	i;

	i = 0;
	while (env->envp[i])
	{
		free(env->envp[i]);
		i++;
	}
	free(env->envp);
}

void	environment_set(t_environment *env,
	const char *name, const char *value)
{
	int	index;

	index = environment_get_index(env, name);
	if (index < 0)
		environment_push_back(env, name, value);
	else
		environment_replace(env, name, value, index);
}

void	environment_swap_remove(t_environment *env, const char *name)
{
	int		index;
	char	*temp;

	index = environment_get_index(env, name);
	if (index < 0)
		return ;
	temp = env->envp[index];
	env->envp[index] = env->envp[env->len - 1];
	env->len -= 1;
	free(temp);
	env->envp[env->len] = NULL;
}

const char	*environment_get(t_environment *env, const char *name)
{
	int		index;
	char	*value;

	index = environment_get_index(env, name);
	if (index < 0)
		return (NULL);
	value = ft_strchr(env->envp[index], '=') + 1;
	return (value);
}
