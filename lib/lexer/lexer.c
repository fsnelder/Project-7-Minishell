/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 14:03:09 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/06 14:03:10 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "util.h"
#include "lexer_utils.h"
#include <stdbool.h>
#include <stdio.h>

const char	*token_type_string(t_token_type type)
{
	switch (type) {
		case PIPE:
			return "PIPE";
		case WORD:
			return "WORD";
		case TOKEN_REDIRECT_IN:
			return "TOKEN_REDIRECT_IN";
		case TOKEN_REDIRECT_OUT:
			return "TOKEN_REDIRECT_OUT";
		case TOKEN_REDIRECT_HEREDOC:
			return "TOKEN_REDIRECT_HEREDOC";
		case TOKEN_REDIRECT_APPEND:
			return "TOKEN_REDIRECT_APPEND";
	}
	return "UNKNOWN";
}

// TODO: debug/remove
void	print_token(void *t)
{
	t_token *token = (t_token*)t;
	printf("Token(%s, %.*s)\n", token_type_string(token->type), (int)token->length, token->token);
}

typedef int	(*t_parse_function)(char, t_lexer*);

static int	dispatch_character(char ch, t_lexer *lexer)
{
	static const t_parse_function	parsers[255] = {
	['"'] = parse_quoted,
	['\''] = parse_quoted,
	['>'] = parse_redirect_out,
	['<'] = parse_redirect_in,
	['|'] = parse_pipe,
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
