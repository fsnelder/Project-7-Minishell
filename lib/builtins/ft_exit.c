/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 09:44:56 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 14:43:09 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool	is_numeric(const char *str)
{
	int	size;

	size = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		size++;
		str++;
	}
	return (size != 0 && *str == '\0');
}

int	ft_exit(const char **args, const char **envp)
{
	(void)envp;
	args++;
	if (args[0] == NULL)
		exit(g_ms_data.exit_code);
	if (!is_numeric(args[0]))
	{
		printf("exit: %s: numeric argument required\n", args[0]);
		exit(255);
	}
	printf("exit\n");
	if (args[1] != NULL)
	{
		printf("exit: too many arguments\n");
		return (GENERAL_ERROR);
	}
	exit((unsigned char)ft_atoi(args[0]));
}
