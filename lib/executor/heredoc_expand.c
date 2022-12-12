/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_expand.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/12 13:30:47 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/12 13:40:34 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor_utils.h"

char	*heredoc_expand(const char *line)
{
	char	*expanded;

	expanded = expand_word(
			line,
			ft_strlen(line),
			(const char **)environ,
			EXPAND_VARIABLES
			)
		.str;
	free((void *)line);
	return (expanded);
}

char	*expand_delimiter(t_token *input)
{
	return (expand_token(input, (const char **)environ, EXPAND_QUOTES));
}

bool	check_should_expand(t_token *input)
{
	size_t	i;

	i = 0;
	while (i < input->length)
	{
		if (input->token[i] == '\'' || input->token[i] == '"')
			return (false);
		i++;
	}
	return (true);
}
