/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 12:41:38 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/06 13:59:42 by fsnelder      ########   odam.nl         */
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
	t_list			*t_redirect;
	const char		*command_name;
	const char		**arguments;
}	t_command;

int	parse(t_list *tokens, t_list **commands);

#endif
