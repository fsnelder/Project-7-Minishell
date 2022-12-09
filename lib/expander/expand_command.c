/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_command.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 13:08:47 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 13:15:35 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include "libft.h"
#include "parser.h"
#include "expand.h"

static void	*token_to_expand(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	return (expand_token(token, (const char **)environ, EXPAND_ALL));
}

static void	expand_redirection(void *ptr)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)ptr;
	if (redirect->redirect_type == REDIRECT_HEREDOC)
		return ;
	redirect->expanded = expand_token(
			redirect->word, (const char **)environ, EXPAND_ALL);
}

static char	**list_arguments_to_array(t_list *arguments)
{
	size_t	size;
	char	**result;
	int		i;

	size = ft_lstsize(arguments);
	result = ft_malloc((size + 1) * sizeof(char *));
	result[size] = NULL;
	i = 0;
	while (arguments)
	{
		result[i] = (char *)arguments->content;
		i++;
		arguments = arguments->next;
	}
	return (result);
}

void	expand_commands(t_list *commands)
{
	t_command	*command;
	t_list		*expanded_args;

	while (commands)
	{
		command = (t_command *)commands->content;
		ft_lstiter(command->redirections, expand_redirection);
		expanded_args = ft_lstmap(command->arguments, token_to_expand, free);
		command->argv = list_arguments_to_array(expanded_args);
		ft_lstclear(&expanded_args, NULL);
		commands = commands->next;
	}
}
