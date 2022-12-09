/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_expand_functions.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 09:31:31 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 14:43:41 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "ft_string.h"
#include "libft.h"
#include "util.h"
#include "expand_utils.h"

void	expand_character(t_expander *expander)
{
	string_push_back(&expander->result, *expander->src);
	expander->src++;
}

void	expand_exit_code(t_expander *expander)
{
	char	*code;

	code = malloc_check(ft_itoa(g_ms_data.exit_code));
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
	string_push_str(&expander->result, expander->src, end);
	expander->src = end + 1;
}

void	expand_double_quote(t_expander *expander)
{
	const char	*end;

	expander->src++;
	end = ft_strchr(expander->src, '"');
	while (expander->src != end)
	{
		if (*expander->src == '$')
			expand_variable(expander);
		else
			expand_character(expander);
	}
	expander->src++;
}