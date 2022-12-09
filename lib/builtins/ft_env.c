/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 09:45:05 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 11:40:54 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_env(const char **args, const char **envp)
{
	t_environment	*env;
	size_t			i;

	env = &g_ms_data.env;
	i = 0;
	while (i < env->len)
	{
		printf("%s\n", env->envp[i]);
		i++;
	}
	return (0);
}
