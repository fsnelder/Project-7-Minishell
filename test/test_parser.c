/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsnelder <fsnelder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 12:29:38 by fsnelder          #+#    #+#             */
/*   Updated: 2022/12/07 13:02:55 by fsnelder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "util.h"
#include <criterion/criterion.h>

static int parse_wrapper(const char *line, t_list **commands) {
	t_list *tokens;
	int result = lexical_analysis(line, &tokens);
	cr_assert(result == SUCCESS);
	return parse(tokens, commands);
}

static t_redirect* get_redirect(t_list *redirects, int index) {
	for (int i = 0; i < index; i++) {
		redirects = redirects->next;
	}
	return (t_redirect*)redirects->content;
}

static t_command* get_command(t_list *redirects, int index) {
	for (int i = 0; i < index; i++) {
		redirects = redirects->next;
	}
	return (t_command*)redirects->content;
}

Test(basic, parser) {
	t_list *commands;
	int result = parse_wrapper("ls", &commands);
	cr_assert(result == SUCCESS);
	cr_assert(commands != NULL);
	cr_assert(commands->next == NULL);
	t_command *cmd = (t_command*)commands->content;
	cr_assert(strcmp(cmd->command_name, "ls") == 0);
}

Test(arguments, parser) {
	t_list *commands;
	int result = parse_wrapper("ls a=b 1 2", &commands);
	cr_assert(result == SUCCESS);
	t_command *cmd = (t_command*)commands->content;
	cr_assert(strcmp((char*)cmd->arguments->content, "a=b") == 0);
	cr_assert(strcmp((char*)cmd->arguments->next->content, "1") == 0);
	cr_assert(strcmp((char*)cmd->arguments->next->next->content, "2") == 0);
}

Test(redirections, parser) {
	t_list *commands;
	int result = parse_wrapper("ls >> 1 << 2 > word", &commands);
	cr_assert(result == SUCCESS);
	t_command *cmd = (t_command*)commands->content;
	t_redirect* a = get_redirect(cmd->redirections, 0);
	cr_assert(a->redirect_type == REDIRECT_APPEND);
	cr_assert(strncmp(a->word->token, "1", a->word->length) == 0);
	t_redirect* b = get_redirect(cmd->redirections, 1);
	cr_assert(b->redirect_type == REDIRECT_HEREDOC);
	cr_assert(strncmp(b->word->token, "2", b->word->length) == 0);
	t_redirect* c = get_redirect(cmd->redirections, 2);
	cr_assert(c->redirect_type == REDIRECT_OUT);
	cr_assert(strncmp(c->word->token, "word", c->word->length) == 0);
}

Test(pipes, parser) {
	t_list *commands;
	int result = parse_wrapper("a | b | c | d", &commands);
	cr_assert(result == SUCCESS);
	cr_assert(strcmp(get_command(commands, 0)->command_name, "a") == 0);
	cr_assert(strcmp(get_command(commands, 1)->command_name, "b") == 0);
	cr_assert(strcmp(get_command(commands, 2)->command_name, "c") == 0);
	cr_assert(strcmp(get_command(commands, 3)->command_name, "d") == 0);
}

Test(pipe_start, parser) {
	t_list *commands;
	int result = parse_wrapper("| a b c", &commands);
	cr_assert(result == GENERAL_ERROR);
}

Test(pipe_end, parser) {
	t_list *commands;
	int result = parse_wrapper("a b c |", &commands);
	cr_assert(result == GENERAL_ERROR);
}

static void assert_general_error(const char *line) {
	t_list *commands;
	int result = parse_wrapper("a b c |", &commands);
	cr_assert(result == GENERAL_ERROR);
}

Test(invalid_redirect, parser) {
	assert_general_error("> >");
	assert_general_error(">> >");
	assert_general_error("<< >");
	assert_general_error("< >");
	assert_general_error("> |");
	assert_general_error(">");
	assert_general_error("| >");
	assert_general_error("1 >");
	assert_general_error("1 > 1 > > | abc");
}
