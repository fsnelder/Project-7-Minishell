/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsnelder <fsnelder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:05:49 by fsnelder          #+#    #+#             */
/*   Updated: 2022/12/07 11:11:30 by fsnelder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "libft.h"
# include "parser.h"

typedef struct s_parser
{
	t_list		**commands;
	t_command	*command;
	t_list		*token;
}	t_parser;

#endif
