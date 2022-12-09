/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 12:06:30 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 14:27:37 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "util.h"
#include "parser.h"
#include "expand.h"
#include "executor.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include "libft.h"

#define PROMPT "minishell -> "

static void	reset_readline(void)
{
	rl_replace_line("", false);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigint_handler(int sig)
{
	// TODO: handle exit code
	printf("\n");
	reset_readline();
}

static int	initialize_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	//signal(SIGQUIT, SIG_IGN);
	return (0);
}

// TODO: remove prototype
void	print_command(void *cptr);

static void	execute_line(const char *line)
{
	t_list	*tokens;
	t_list	*commands;
	int		result;

	result = lexical_analysis(line, &tokens);
	if (result != SUCCESS)
		return ;
	result = parse(tokens, &commands);
	if (result != SUCCESS)
	{
		ft_lstclear(&tokens, free);
		return ;
	}
	expand_commands(commands);
	result = execute(commands);
	ft_lstclear(&commands, command_destroy);
	ft_lstclear(&tokens, free);
}

int	main(int argc, char *argv[], char *environ[])
{
	char	*line;

	(void)argc;
	(void)argv;
	init_minishell();
	initialize_signal_handlers();
	while (true)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		else if (*line == '\0')
			continue ;
		add_history(line);
		execute_line(line);
		free(line);
	}
	destroy_minishell();
	printf("exit\n");
	return (g_ms_data.exit_code);
}
