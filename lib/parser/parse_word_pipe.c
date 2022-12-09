/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_word_pipe.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 10:18:55 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 10:24:43 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_utils.h"
#include "util.h"
#include <stdio.h>

int	parse_pipe(t_parser *parser, t_token *token)
{
	if (!parser->command || parser->token->next == NULL)
	{
		printf("parse error near `%.*s'\n", (int)token->length, token->token);
		return (GENERAL_ERROR);
	}
	parser_flush_command(parser);
	parser->token = parser->token->next;
	return (SUCCESS);
}

int	parse_word(t_parser *parser, t_token *token)
{
	parser_init_command(parser);
	ft_lstadd_back(&parser->command->arguments, malloc_check(ft_lstnew(token)));
	parser->token = parser->token->next;
	return (SUCCESS);
}
