/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 13:29:40 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/08 10:38:03 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "ft_string.h"
# include "lexer.h"

t_string	expand_word(const char *src, size_t len, const char **envp);
char		*expand_token(t_token *token, const char **envp);

#endif
