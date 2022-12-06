/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_lexer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 11:26:05 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/06 11:48:46 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "util.h"
#include <criterion/criterion.h>

static void expect_success(const char *line) {
	t_list *tokens;
	int result = lexical_analysis(line, &tokens);
	cr_assert(result == SUCCESS);
	ft_lstclear(&tokens, free);
}

static t_token* get_token(t_list *tokens, int index) {
	for (int i = 0; i < index; i++) {
		tokens = tokens->next;
	}
	return (t_token*)tokens->content;
}

Test(basic, lexer) {
	expect_success("line < > |");
}

Test(double_within_single, lexer) {
	expect_success("line < > '\" asdf' |");
}

Test(single_within_double, lexer) {
	expect_success("\" .  ''' asdf ' ''\"");
}

Test(unclosed_quote, lexer) {
	t_list *tokens;
	int result = lexical_analysis("'", &tokens);
	cr_assert(result == GENERAL_ERROR);
	ft_lstclear(&tokens, free);
}

Test(unclosed_double_quote, lexer) {
	t_list *tokens;
	int result = lexical_analysis("\"", &tokens);
	cr_assert(result == GENERAL_ERROR);
	ft_lstclear(&tokens, free);
}

Test(token_verification, lexer) {
	t_list *tokens;
	lexical_analysis("LINE > <", &tokens);
	cr_assert(ft_lstsize(tokens) == 3);
	cr_assert(get_token(tokens, 0)->type == WORD);
	cr_assert(get_token(tokens, 0)->length == 4);
	cr_assert(strncmp("LINE", get_token(tokens, 0)->token, 4) == 0);
	cr_assert(get_token(tokens, 1)->type == REDIRECT_OUT);
	cr_assert(get_token(tokens, 2)->type == REDIRECT_IN);
	ft_lstclear(&tokens, free);
}

Test(token_verification_operators, lexer) {
	t_list *tokens;
	lexical_analysis("| << >>", &tokens);
	cr_assert(ft_lstsize(tokens) == 3);
	cr_assert(get_token(tokens, 0)->type == PIPE);
	cr_assert(get_token(tokens, 1)->type == REDIRECT_HEREDOC);
	cr_assert(get_token(tokens, 2)->type == REDIRECT_APPEND);
	ft_lstclear(&tokens, free);
}
