/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 14:17:08 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 11:39:18 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "environment.h"
#include <stdlib.h>
#include <stdio.h>

t_minishell_data	g_ms_data;

void	init_minishell(void)
{
	g_ms_data.exit_code = 0;
	g_ms_data.env = environment_init((const char **)environ);
}

static void	abort_program(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	*malloc_check(void *ptr)
{
	if (!ptr)
	{
		abort_program("malloc");
	}
	return (ptr);
}

void	*ft_malloc(size_t n)
{
	return (malloc_check(malloc(n)));
}
