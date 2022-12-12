/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_string_2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/12 13:49:15 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/12 13:50:46 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "util.h"
#include "libft.h"
#include <stdlib.h>

char	*string_cstr(t_string *str)
{
	return (str->str);
}
