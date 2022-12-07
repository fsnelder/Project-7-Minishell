/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsnelder <fsnelder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:41:38 by fsnelder          #+#    #+#             */
/*   Updated: 2022/12/07 13:05:42 by fsnelder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "lexer.h"

typedef enum e_redirect_type
{
	REDIRECT_IN,
	REDIRECT_APPEND,
	REDIRECT_OUT,
	REDIRECT_HEREDOC
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type	redirect_type;
	t_token			*word;
}	t_redirect;

typedef struct s_command
{
	t_list			*redirections;
	const char		*command_name;
	t_list			*arguments;
}	t_command;

int		parse(t_list *tokens, t_list **commands);
void	command_destroy(void *command_ptr);

#endif
