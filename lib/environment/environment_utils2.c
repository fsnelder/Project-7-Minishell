/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment_utils2.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 11:45:34 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 11:47:58 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "grammar.h"
#include "libft.h"
#include <stdbool.h>

bool	is_valid_identifier(const char *name)
{
	if (ft_strchr(WORD_START, *name) == NULL)
		return (false);
	while (*name)
	{
		if (ft_strchr(WORD_ENTRY, *name) == NULL)
			return (false);
		name++;
	}
	return (true);
}
