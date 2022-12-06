/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 10:00:56 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/06 10:07:09 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_utils.h"
#include "util.h"

void	lexer_init(t_lexer *lexer, const char *line)
{
	lexer->current = NULL;
	lexer->tokens = NULL;
	lexer->line = line;
}

void	lexer_destroy(t_lexer *lexer)
{
	ft_lstclear(&lexer->tokens, free);
	free(lexer->current);
}

void	lexer_new_token(
	t_lexer *lexer, t_token_type type, const char *s, size_t len)
{
	lexer->current = ft_malloc(1 * sizeof(t_token));
	lexer->current->length = len;
	lexer->current->token = s;
	lexer->current->type = type;
}

void	lexer_flush_token(t_lexer *lexer)
{
	if (!lexer->current)
		return ;
	ft_lstadd_back(&lexer->tokens, malloc_check(ft_lstnew(lexer->current)));
	lexer->current = NULL;
}

void	token_add_string(t_lexer *lexer, const char *s, size_t len)
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
