/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 14:14:52 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/05 15:34:10 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "util.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct s_lexer
{
	t_token		*current;
	t_list		*tokens;
	const char	*line;
}	t_lexer;

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

static void	lexer_init(t_lexer *lexer, const char *line)
{
	lexer->current = NULL;
	lexer->tokens = NULL;
	lexer->line = line;
}

static void	lexer_destroy(t_lexer *lexer)
{
	ft_lstclear(&lexer->tokens, free);
	free(lexer->current);
}

static void	lexer_new_token(
	t_lexer *lexer, t_token_type type, const char *s, size_t len)
{
	lexer->current = ft_malloc(1 * sizeof(t_token));
	lexer->current->length = len;
	lexer->current->token = s;
	lexer->current->type = type;
}

static void	lexer_flush_token(t_lexer *lexer)
{
	if (!lexer->current)
		return ;
	ft_lstadd_back(&lexer->tokens, malloc_check(ft_lstnew(lexer->current)));
	lexer->current = NULL;
}

static void	token_add_string(t_lexer *lexer, const char *s, size_t len)
{
	if (lexer->current)
	{
		if (lexer->current->type == WORD)
			lexer->current->length += len;
		else
		{
			lexer_flush_token(lexer);
			lexer_new_token(lexer, WORD, s, len);
		}
	}
	else
		lexer_new_token(lexer, WORD, s, len);
}

static int	parse_quoted(char ch, t_lexer *lexer)
{
	char	quote;
	char	*end;

	quote = *lexer->line;
	end = ft_strchr(lexer->line + 1, quote);
	if (!end)
	{
		printf("expected closing quote: %c\n", ch);
		return (GENERAL_ERROR);
	}
	token_add_string(lexer, lexer->line, (end - lexer->line) + 1);
	lexer->line = end;
	return (SUCCESS);
}

static int	parse_generic(char ch, t_lexer *lexer)
{
	token_add_string(lexer, lexer->line, 1);
	return (SUCCESS);
}

static int parse_redirect_in(char ch, t_lexer *lexer)
{
	if (lexer->current && lexer->current->type == REDIRECT_IN)
	{
		lexer->current->type = REDIRECT_HEREDOC;
		lexer->current->length += 1;
	}
	else
	{
		lexer_flush_token(lexer);
		lexer_new_token(lexer, REDIRECT_IN, lexer->line, 1);
	}
	return (SUCCESS);
}

static int parse_redirect_out(char ch, t_lexer *lexer)
{
	if (lexer->current && lexer->current->type == REDIRECT_OUT)
	{
		lexer->current->type = REDIRECT_APPEND;
		lexer->current->length += 1;
	}
	else
	{
		lexer_flush_token(lexer);
		lexer_new_token(lexer, REDIRECT_OUT, lexer->line, 1);
	}
	return (SUCCESS);
}

static int parse_pipe(char ch, t_lexer *lexer)
{
	lexer_flush_token(lexer);
	lexer_new_token(lexer, PIPE, lexer->line, 1);
	return (SUCCESS);
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
