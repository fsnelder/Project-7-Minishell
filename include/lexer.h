/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 14:06:30 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/05 15:23:37 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <stddef.h>

typedef enum e_token_type {
	PIPE,
	WORD,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_HEREDOC,
	REDIRECT_APPEND
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	const char		*token;
	size_t			length;
}	t_token;

t_list	*lexical_analysis(const char *line);
void	print_token(void *t); // TODO: remove

#endif
