/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 14:05:49 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 10:19:32 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "libft.h"
# include "parser.h"

typedef struct s_parser
{
	t_list		**commands;
	t_command	*command;
	t_list		*token;
}	t_parser;

int		parse_redirection(
			t_parser *parser, t_redirect_type type, t_token *token);
int		parse_append(t_parser *parser, t_token *token);
int		parse_heredoc(t_parser *parser, t_token *token);
int		parse_in(t_parser *parser, t_token *token);
int		parse_out(t_parser *parser, t_token *token);

int		parse_pipe(t_parser *parser, t_token *token);
int		parse_word(t_parser *parser, t_token *token);

void	parser_init_command(t_parser *parser);
void	command_add_redirect(
			t_command *command, t_redirect_type type, t_token *word);

void	redirect_destroy(void *redirect);
void	command_destroy(void *command_ptr);
void	parser_destroy(t_parser *parser);
void	parser_flush_command(t_parser *parser);

#endif
