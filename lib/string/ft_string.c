/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_string.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 13:19:32 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/12 13:49:23 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "util.h"
#include "libft.h"
#include <stdlib.h>

t_string	string_new(size_t initial_capacity)
{
	t_string	str;

	str.cap = initial_capacity + 1;
	str.str = ft_malloc(str.cap * sizeof(char));
	str.len = 0;
	str.str[str.len] = '\0';
	return (str);
}

void	string_destroy(t_string *str)
{
	free(str->str);
	str->str = NULL;
}

void	string_resize_if_needed(t_string *str)
{
	char	*next;

	if (str->len + 1 == str->cap)
	{
		str->cap *= 2;
		next = ft_malloc(str->cap * sizeof(char));
		ft_memcpy(next, str->str, str->len + 1);
		free(str->str);
		str->str = next;
	}
}

void	string_push_back(t_string *str, char ch)
{
	string_resize_if_needed(str);
	str->str[str->len] = ch;
	str->len++;
	str->str[str->len] = '\0';
}

void	string_push_str(t_string *str, const char *src, const char *end)
{
	while (src != end)
	{
		string_push_back(str, *src);
		src++;
	}
}
