/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 10:02:18 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 10:26:06 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H

typedef struct s_lexer
{
	t_token		*current;
	t_list		**tokens;
	const char	*line;
}	t_lexer;

int		parse_quoted(char ch, t_lexer *lexer);
int		parse_generic(char ch, t_lexer *lexer);
int		parse_redirect_in(char ch, t_lexer *lexer);
int		parse_redirect_out(char ch, t_lexer *lexer);
int		lex_pipe(char ch, t_lexer *lexer);

void	lexer_init(t_lexer *lexer, t_list **tokens, const char *line);
void	lexer_destroy(t_lexer *lexer);
void	lexer_new_token(
			t_lexer *lexer, t_token_type type, const char *s, size_t len);
void	lexer_flush_token(t_lexer *lexer);
void	token_add_string(t_lexer *lexer, const char *s, size_t len);

#endif
