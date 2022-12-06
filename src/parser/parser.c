/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 12:33:29 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/06 14:01:08 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "lexer.h"
#include "parser.h"

static void	*parser_init(t_command *command, t_list *tokens)
{
	command->type = NULL;
	command->command_name = NULL;
	command->tokens = tokens;
}

static void	*parse_nodes(t_command *command_list)
{
	
}

int	parse(t_list *tokens, t_list **commands)
{
	t_command	*command_list;
	int	result;

	parser_init(&command_list, tokens);
	while (command_list->tokens)
	{
		result = parse_nodes(command_list);
	}
	return (result);
}
