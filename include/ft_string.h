/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsnelder <fsnelder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:13:58 by fsnelder          #+#    #+#             */
/*   Updated: 2022/12/07 14:56:31 by fsnelder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stddef.h>

typedef struct s_string
{
	char	*str;
	size_t	len;
	size_t	cap;
}	t_string;

t_string	string_new(size_t initial_capacity);
void		string_destroy(t_string *str);
void		string_push_back(t_string *str, char ch);
void		string_push_str(t_string *str, const char *begin, const char *end);
char		*string_cstr(t_string *str);

#endif
