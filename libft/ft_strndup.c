/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsnelder <fsnelder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:44:50 by fsnelder          #+#    #+#             */
/*   Updated: 2022/12/07 11:16:13 by fsnelder         ###   ########.fr       */
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
#include <libft.h>

static size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_strndup(const char *src, size_t n)
{
	char	*result;

	n = ft_min(ft_strlen(src), n);
	result = malloc(n + 1);
	if (result == 0)
		return (NULL);
	result[n] = '\0';
	ft_memcpy(result, src, n);
	return (result);
}
