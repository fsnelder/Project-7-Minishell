/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 16:13:10 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 10:54:21 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct s_arguments {
	const char	**args;
	bool		print_newline;
}	t_arguments;

static bool	is_n_option(const char *s)
{
	if (*s != '-')
		return (false);
	s++;
	if (*s != 'n')
		return (false);
	while (*s == 'n')
		s++;
	return (*s == '\0');
}

static void	parse_option(t_arguments *arguments)
{
	while (*arguments->args)
	{
		if (is_n_option(*arguments->args))
		{
			arguments->args++;
			arguments->print_newline = false;
		}
		else
			break ;
	}
}

int	ft_echo(const char **argv, const char **envp)
{
	t_arguments	args;

	(void)envp;
	args.args = argv + 1;
	args.print_newline = true;
	parse_option(&args);
	while (*args.args)
	{
		ft_putstr_fd((char *)*args.args, STDOUT_FILENO);
		if (*(args.args + 1) != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		args.args++;
	}
	if (args.print_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
