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

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	unsigned int	j;
	unsigned int	k;
	char			*s2;

	k = 0;
	while (s1[k] != '\0')
		k++;
	s2 = malloc(k + 1);
	if (s2 == 0)
		return (NULL);
	j = 0;
	while (k > 0)
	{
		s2[j] = s1[j];
		j++;
		k--;
	}
	s2[j] = '\0';
	return (s2);
}
