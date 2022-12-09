/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 13:06:52 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 13:43:56 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

void	free_split(char **strings)
{
	int	i;

	if (!strings)
		return ;
	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

int	free_fds_and_return(int result, int nfds, ...)
{
	va_list	ap;
	int		fd;

	va_start(ap, nfds);
	while (nfds)
	{
		fd = va_arg(ap, int);
		if (fd != -1)
			close(fd);
		nfds--;
	}
	va_end(ap);
	return (result);
}
