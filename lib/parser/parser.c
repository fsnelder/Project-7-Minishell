/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsnelder <fsnelder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:33:29 by fsnelder          #+#    #+#             */
/*   Updated: 2022/12/07 12:48:36 by fsnelder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "lexer.h"
#include "parser.h"
#include "parser_utils.h"
#include "libft.h"
#include "util.h"
#include <stdio.h>

char* get_redirect_string(t_redirect_type type) {
	switch (type) {
		case REDIRECT_IN:
			return "<";
		case REDIRECT_APPEND:
			return ">>";
		case REDIRECT_OUT:
			return ">";
		case REDIRECT_HEREDOC:
			return "<<";
	}
	abort();
}

// Command: <name> , redirections: [ <redirections> ] arguments: [ <arguments> ]
void	print_command(void *cptr)
{
	t_command *command = (t_command*)cptr;
	printf("Command: %s, redirections: [", command->command_name);
	for (t_list *x = command->redirections; x != NULL; x = x->next) {
		t_redirect *r = (t_redirect *)x->content;
		if (x != command->redirections) {
			printf(",");
		}
		printf(" %s %.*s", get_redirect_string(r->redirect_type), (int)r->word->length, r->word->token);
	}
	printf(" ]");
	printf(" arguments: [");
	t_list *x = command->arguments;
	while (x != NULL) {
		char *arg = (char *)x->content;
		if (x != command->arguments) {
			printf(",");
		}
		printf(" %s", arg);
		x = x->next;
	}
	printf(" ]");
	printf("\n");
}

static void	parser_init(t_parser *parser, t_list *tokens, t_list **commands)
{
	*commands = NULL;
	parser->command = NULL;
	parser->commands = commands;
	parser->token = tokens;
}

static void	command_destroy(void *command_ptr)
{
	t_command	*command;

	if (!command_ptr)
		return ;
	command = (t_command *)command_ptr;
	free((void *)command->command_name);
	ft_lstclear(&command->arguments, free);
	ft_lstclear(&command->redirections, free);
}

static void	parser_destroy(t_parser *parser)
{
	command_destroy(parser->command);
	ft_lstclear(parser->commands, command_destroy);
}

static void	parser_init_command(t_parser *parser)
{
	if (parser->command != NULL)
		return ;
	parser->command = ft_malloc(1 * sizeof(t_command));
	parser->command->command_name = NULL;
	parser->command->arguments = NULL;
	parser->command->redirections = NULL;
}

static void	parser_flush_command(t_parser *parser)
{
	if (parser->command == NULL)
		return ;
	ft_lstadd_back(parser->commands, malloc_check(ft_lstnew(parser->command)));
	parser->command = NULL;
}

static void	command_add_redirect(
		t_command *command, t_redirect_type type, t_token *word)
{
	t_redirect	*redirect;

	redirect = ft_malloc(1 * sizeof(t_redirect));
	redirect->redirect_type = type;
	redirect->word = word;
	ft_lstadd_back(&command->redirections, malloc_check(ft_lstnew(redirect)));
}

static int	parse_redirection(t_parser *parser, t_redirect_type type, t_token *token)
{
	t_token	*next;

	parser_init_command(parser);
	if (parser->token->next == NULL)
	{
		printf("parse error near `\\n'\n");
		return (GENERAL_ERROR);
	}
	next = (t_token *)parser->token->next->content;
	if (next->type != WORD)
	{
		printf("parse error near `%.*s'\n", (int)next->length, next->token);
		return (GENERAL_ERROR);
	}
	command_add_redirect(parser->command, type, next);
	parser->token = parser->token->next->next;
	return (SUCCESS);
}

static int	parse_append(t_parser *parser, t_token *token)
{
	return (parse_redirection(parser, REDIRECT_APPEND, token));
}

static int	parse_heredoc(t_parser *parser, t_token *token)
{
	return (parse_redirection(parser, REDIRECT_HEREDOC, token));
}

static int	parse_in(t_parser *parser, t_token *token)
{
	return (parse_redirection(parser, REDIRECT_IN, token));
}

static int	parse_out(t_parser *parser, t_token *token)
{
	return (parse_redirection(parser, REDIRECT_OUT, token));
}

static int	parse_pipe(t_parser *parser, t_token *token)
{
	if (!parser->command || parser->token->next == NULL)
	{
		printf("parse error near `%.*s'\n", (int)token->length, token->token);
		return (GENERAL_ERROR);
	}
	parser_flush_command(parser);
	parser->token = parser->token->next;
	return (SUCCESS);
}

static int	parse_word(t_parser *parser, t_token *token)
{
	char	*word;

	parser_init_command(parser);
	word = malloc_check(ft_strndup(token->token, token->length));
	if (parser->command->command_name == NULL)
		parser->command->command_name = word;
	else
		ft_lstadd_back(
			&parser->command->arguments, malloc_check(ft_lstnew(word)));
	parser->token = parser->token->next;
	return (SUCCESS);
}

typedef int	(*t_token_parser)(t_parser *, t_token *);

static int	parse_node(t_parser *parser)
{
	static const t_token_parser	parsers[] = {
	[TOKEN_REDIRECT_APPEND] = parse_append,
	[TOKEN_REDIRECT_HEREDOC] = parse_heredoc,
	[TOKEN_REDIRECT_IN] = parse_in,
	[TOKEN_REDIRECT_OUT] = parse_out,
	[PIPE] = parse_pipe,
	[WORD] = parse_word
	};
	t_token						*token;

	token = (t_token *)parser->token->content;
	return ((parsers[token->type])(parser, token));
}

int	parse(t_list *tokens, t_list **commands)
{
	t_parser	parser;
	int			result;

	parser_init(&parser, tokens, commands);
	while (parser.token)
	{
		result = parse_node(&parser);
		if (result != SUCCESS)
		{
			parser_destroy(&parser);
			return (result);
		}
	}
	parser_flush_command(&parser);
	parser.commands = NULL;
	return (SUCCESS);
}
