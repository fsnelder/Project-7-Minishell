/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsnelder <fsnelder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:06:30 by fsnelder          #+#    #+#             */
/*   Updated: 2022/12/07 11:53:10 by fsnelder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <stddef.h>

typedef enum e_token_type {
	PIPE,
	WORD,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_HEREDOC,
	TOKEN_REDIRECT_APPEND
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	const char		*token;
	size_t			length;
}	t_token;

int		lexical_analysis(const char *line, t_list **tokens);
void	print_token(void *t); // TODO: remove

#endif
