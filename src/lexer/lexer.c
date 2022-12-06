/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 14:14:52 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/06 10:06:34 by fsnelder      ########   odam.nl         */
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
		case REDIRECT_IN:
			return "REDIRECT_IN";
		case REDIRECT_OUT:
			return "REDIRECT_OUT";
		case REDIRECT_HEREDOC:
			return "REDIRECT_HEREDOC";
		case REDIRECT_APPEND:
			return "REDIRECT_APPEND";
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

t_list	*lexical_analysis(const char *line)
{
	t_lexer	lexer;
	t_list	*tokens;
	int		result;

	lexer_init(&lexer, line);
	while (*lexer.line != '\0')
	{
		result = parse_character(*lexer.line, &lexer);
		if (result != SUCCESS)
		{
			lexer_destroy(&lexer);
			return (NULL);
		}
		lexer.line++;
	}
	lexer_flush_token(&lexer);
	tokens = lexer.tokens;
	lexer.tokens = NULL;
	lexer_destroy(&lexer);
	return (tokens);
}
