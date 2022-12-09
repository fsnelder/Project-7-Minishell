/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_files.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 10:06:09 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 10:11:13 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"
#include "parser.h"
#include "util.h"
#include <stdio.h>

int	parse_append(t_parser *parser, t_token *token)
{
	return (parse_redirection(parser, REDIRECT_APPEND, token));
}

int	parse_heredoc(t_parser *parser, t_token *token)
{
	return (parse_redirection(parser, REDIRECT_HEREDOC, token));
}

int	parse_in(t_parser *parser, t_token *token)
{
	return (parse_redirection(parser, REDIRECT_IN, token));
}

int	parse_out(t_parser *parser, t_token *token)
{
	return (parse_redirection(parser, REDIRECT_OUT, token));
}

int	parse_redirection(t_parser *parser, t_redirect_type type, t_token *token)
{
	t_token	*next;

	parser_init_command(parser);
	if (parser->token->next == NULL)
	{
		printf("parse error near `\\n'\n");
		return (GENERAL_ERROR);
	}
	next = (t_token *)parser->token->next->content;
	if (next->type != WORD)
	{
		printf("parse error near `%.*s'\n", (int)next->length, next->token);
		return (GENERAL_ERROR);
	}
	command_add_redirect(parser->command, type, next);
	parser->token = parser->token->next->next;
	return (SUCCESS);
}