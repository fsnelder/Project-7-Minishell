/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 11:14:42 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 12:00:40 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "environment_utils.h"
#include "util.h"
#include "libft.h"

void	environment_resize(t_environment *env)
{
	char	**new_env;

	if (env->len + 1 == env->cap)
	{
		env->cap *= 2;
		new_env = ft_malloc(env->cap * sizeof(char *));
		ft_memcpy(new_env, env->envp, (env->len + 1) * sizeof(char *));
		free(env->envp);
		env->envp = new_env;
		environ = env->envp;
	}
}

int	environment_get_index(t_environment *env, const char *name)
{
	int		index;
	char	*end;
	size_t	len;

	index = 0;
	len = ft_strlen(name);
	while (index < (int)env->len)
	{
		end = ft_strchr(env->envp[index], '=');
		if (len == (size_t)(end - env->envp[index])
			&& ft_strncmp(name, env->envp[index], len) == 0)
			return (index);
		index += 1;
	}
	return (-1);
}

static char	*make_environment_entry(const char *name, const char *value)
{
	char	*temp;
	char	*result;

	temp = malloc_check(ft_strjoin(name, "="));
	result = malloc_check(ft_strjoin(temp, value));
	free(temp);
	return (result);
}

void	environment_push_back(t_environment *env,
			const char *name, const char *value)
{
	environment_resize(env);
	env->envp[env->len] = make_environment_entry(name, value);
	env->envp[env->len + 1] = NULL;
	env->len += 1;
}

// precondition: name is present at the index in env->envp
void	environment_replace(t_environment *env,
			const char *name, const char *value, int index)
{
	free(env->envp[index]);
	env->envp[index] = make_environment_entry(name, value);
}
