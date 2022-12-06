/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 12:33:29 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/06 14:27:06 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "lexer.h"
#include "parser.h"
#include "parser_utils.h"

static void	parser_init(t_parser *parser, t_list *tokens, t_list **commands)
{
	parser->commands = commands;
	parser->token = tokens;
}

typedef int	(*t_token_parser)(t_parser *);

static int	parse_node(t_parser *parser)
{
	// static const t_token_parser	parsers[] = {
	// [TOKEN_REDIRECT_APPEND] = parse_word,
	// [TOKEN_REDIRECT_HEREDOC] = parse_word,
	// [TOKEN_REDIRECT_IN] = parse_word,
	// [TOKEN_REDIRECT_OUT] = parse_word,
	// [PIPE] = parse_pipe,
	// [WORD] = parse_word
	// };
	// // TODO: parse
	// ((t_token*)parser->token->content)->length;
	parser->token = parser->token->next;
	return (SUCCESS);
}

int	parse(t_list *tokens, t_list **commands)
{
	t_parser	parser;
	int			result;

	parser_init(&parser, tokens, commands);
	while (parser.token)
	{
		result = parse_node(&parser);
		if (result != SUCCESS)
		{
			return (result);
		}
	}
	return (SUCCESS);
}
