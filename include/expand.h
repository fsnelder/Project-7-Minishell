/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 13:29:40 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 13:16:11 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "ft_string.h"
# include "lexer.h"

// to use as `to_expand` parameter
# define EXPAND_QUOTES "'\""
# define EXPAND_VARIABLES "$"
# define EXPAND_ALL "$\"'"

t_string	expand_word(
				const char *src,
				size_t len, const char **envp, const char *to_expand);
char		*expand_token(
				t_token *token, const char **envp, const char *to_expand);
void		expand_commands(t_list *commands);

#endif
