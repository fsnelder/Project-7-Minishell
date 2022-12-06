/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 14:05:49 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/06 14:06:39 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "libft.h"

typedef struct s_parser
{
	t_list	**commands;
	t_list	*token;
}	t_parser;

#endif
