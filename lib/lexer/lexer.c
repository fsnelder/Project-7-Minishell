/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 14:03:09 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 14:42:50 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "util.h"
#include "lexer_utils.h"
#include <stdbool.h>
#include <stdio.h>

typedef int	(*t_parse_function)(char, t_lexer*);

static int	dispatch_character(char ch, t_lexer *lexer)
{
	static const t_parse_function	parsers[255] = {
	['"'] = parse_quoted,
	['\''] = parse_quoted,
	['>'] = parse_redirect_out,
	['<'] = parse_redirect_in,
	['|'] = lex_pipe,
	};
	int								index;

	index = (unsigned char)ch;
	if (parsers[index])
		return ((parsers[index])(ch, lexer));
	else
		return (parse_generic(ch, lexer));
}

static int	parse_character(char ch, t_lexer *lexer)
{
	if (ft_isspace(ch))
		lexer_flush_token(lexer);
	else
		return (dispatch_character(ch, lexer));
	return (SUCCESS);
}

int	lexical_analysis(const char *line, t_list **tokens)
{
	t_lexer	lexer;
	int		result;

	lexer_init(&lexer, tokens, line);
	while (*lexer.line != '\0')
	{
		result = parse_character(*lexer.line, &lexer);
		if (result != SUCCESS)
		{
			lexer_destroy(&lexer);
			return (result);
		}
		lexer.line++;
	}
	lexer_flush_token(&lexer);
	lexer.tokens = NULL;
	lexer_destroy(&lexer);
	return (SUCCESS);
}
