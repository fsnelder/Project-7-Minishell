/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 13:36:49 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 09:59:42 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "lexer.h"
#include "ft_string.h"
#include "libft.h"
#include "util.h"
#include "expand_utils.h"
#include <assert.h> //TODO: REMOVE

void	expander_init(
		t_expander *expander, const char *src, size_t len, const char **envp)
{
	expander->src = src;
	expander->end = src + len;
	expander->envp = envp;
	expander->result = string_new(len);
}

/*
<variable> = "$" ( <word> | "?" )
<word> = "_" | ALPHA <word_character>*
<word_character> = "_" | ALPHA | NUMERIC
*/

const char	*ft_getenv(const char *begin, const char *end, const char **envp)
{
	size_t	len;

	len = end - begin;
	while (*envp != NULL)
	{
		if (ft_strncmp(begin, *envp, len) == 0 && (*envp)[len] == '=')
			return (*envp + len + 1);
		envp++;
	}
	return (NULL);
}

void	expand_environment_variable(t_expander *expander)
{
	const char	*begin;
	const char	*end;
	const char	*variable;

	begin = expander->src;
	while (*expander->src != '\0'
		&& ft_strchr(WORD_ENTRY, *expander->src) != NULL)
	{
		expander->src++;
	}
	end = expander->src;
	variable = ft_getenv(begin, end, expander->envp);
	if (variable != NULL)
	{
		string_push_str(
			&expander->result, variable, variable + ft_strlen(variable));
	}
}

typedef void	(*t_expander_function)(t_expander *);

void	expand_dispatch(t_expander *expander, const char *to_expand)
{
	static const t_expander_function	expanders[255] = {
	['$'] = expand_variable,
	['\''] = expand_single_quote,
	['"'] = expand_double_quote
	};
	int									ch;

	ch = (unsigned int)*expander->src;
	if (expanders[ch] == NULL || ft_strchr(to_expand, ch) == NULL)
		expand_character(expander);
	else
		(expanders[ch])(expander);
}