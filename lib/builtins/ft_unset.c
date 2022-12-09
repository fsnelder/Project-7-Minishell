/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unset.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 09:45:13 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 11:49:39 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "environment.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int	ft_unset(const char **args, const char **envp)
{
	t_environment	*env;
	int				result;

	args++;
	env = &g_ms_data.env;
	result = SUCCESS;
	while (*args)
	{
		if (!is_valid_identifier(*args))
		{
			printf("unset: `%s': not a valid identifier\n", *args);
			result = GENERAL_ERROR;
		}
		else
		{
			environment_swap_remove(env, *args);
		}
		args++;
	}
	return (result);
}
