/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 10:16:06 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 13:07:20 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"
#include "parser.h"
#include "util.h"
#include <stdio.h>

void	redirect_destroy(void *redirect)
{
	free(((t_redirect *)redirect)->expanded);
	free(redirect);
}

void	command_destroy(void *command_ptr)
{
	t_command	*command;

	if (!command_ptr)
		return ;
	command = (t_command *)command_ptr;
	ft_lstclear(&command->arguments, NULL);
	ft_lstclear(&command->redirections, redirect_destroy);
	free_split(command->argv);
	free(command_ptr);
}

void	parser_destroy(t_parser *parser)
{
	command_destroy(parser->command);
	ft_lstclear(parser->commands, command_destroy);
}

void	parser_flush_command(t_parser *parser)
{
	if (parser->command == NULL)
		return ;
	ft_lstadd_back(parser->commands, malloc_check(ft_lstnew(parser->command)));
	parser->command = NULL;
}
