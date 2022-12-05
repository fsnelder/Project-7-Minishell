/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 13:44:50 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/05 13:44:51 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 13:44:50 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/05 13:44:51 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int		i;
	unsigned const char	*j1;
	unsigned const char	*j2;

	j1 = s1;
	j2 = s2;
	i = 0;
	while (n > 0)
	{
		if (j1[i] != j2[i])
			return (j1[i] - j2[i]);
		i++;
		n--;
	}
	return (0);
}
