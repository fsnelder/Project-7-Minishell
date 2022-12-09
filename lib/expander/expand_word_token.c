/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_word_token.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 09:52:39 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 09:53:16 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expand.h"
#include "lexer.h"
#include "ft_string.h"
#include "libft.h"
#include "util.h"
#include "expand_utils.h"

t_string	expand_word(
	const char *src, size_t len, const char **envp, const char *to_expand)
{
	t_expander	expander;

	expander_init(&expander, src, len, envp);
	while (expander.src != expander.end)
	{
		expand_dispatch(&expander, to_expand);
	}
	return (expander.result);
}

char	*expand_token(t_token *token, const char **envp, const char *to_expand)
{
	return (expand_word(token->token, token->length, envp, to_expand).str);
}
