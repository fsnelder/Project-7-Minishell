/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtins.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 15:28:52 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 15:41:01 by fsnelder      ########   odam.nl         */
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


typedef int	(*t_builtin_function)(const char **, const char**);

int	get_builtin_index(const char *name)
{
	static const char	*builtins[] = {
		"pwd",
		"cd",
		"echo",
		"env",
		"exit",
		"export",
		"unset",
		NULL
	};
	int					i;

	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strncmp(builtins[i], name, UINT64_MAX) == 0)
			return (i);
		i++;
	}
	return (-1);
}

bool	is_builtin(const char *name)
{
	return (name && get_builtin_index(name) != -1);
}


// precondition: command is a builtin confirmed by `is_builtin(args[0])`
int	dispatch_builtin(t_command *command, char **args)
{
	static const t_builtin_function	builtins[] = {
		ft_pwd,
		ft_cd,
		ft_echo,
		ft_env,
		ft_exit,
		ft_export,
		ft_unset
	};

	return (
		(builtins[get_builtin_index(
					args[0])])((const char **)args, (const char **)environ));
}
