/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_expand_functions.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 09:31:31 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/08 09:44:27 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "ft_string.h"
#include "libft.h"
#include "util.h"
#include "expand_utils.h"
#include <assert.h> //TODO: REMOVE

void	expand_character(t_expander *expander)
{
	string_push_back(&expander->result, *expander->src);
	expander->src++;
}

void	expand_exit_code(t_expander *expander)
{
	char	*code;

	// TODO: handle real exit code
	code = malloc_check(ft_itoa(0));
	string_push_str(&expander->result, code, code + ft_strlen(code));
	free(code);
	expander->src++;
}

void	expand_variable(t_expander *expander)
{
	expander->src++;
	if (*expander->src == '\0' || ft_strchr(WORD_START, *expander->src) == NULL)
	{
		if (*expander->src == '?')
			expand_exit_code(expander);
		else
			string_push_back(&expander->result, '$');
	}
	else
		expand_environment_variable(expander);
}

void	expand_single_quote(t_expander *expander)
{
	const char	*end;

	expander->src++;
	end = ft_strchr(expander->src, '\'');
	assert(end != NULL); // TODO: remove
	string_push_str(&expander->result, expander->src, end);
	expander->src = end + 1;
}

void	expand_double_quote(t_expander *expander)
{
	const char	*end;

	expander->src++;
	end = ft_strchr(expander->src, '"');
	assert(end != NULL); // TODO: remove
	while (expander->src != end)
	{
		if (*expander->src == '$')
			expand_variable(expander);
		else
			expand_character(expander);
	}
	expander->src++;
}