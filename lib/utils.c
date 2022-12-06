/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 14:17:08 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/05 15:18:03 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

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
