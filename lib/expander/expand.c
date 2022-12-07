/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsnelder <fsnelder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:36:49 by fsnelder          #+#    #+#             */
/*   Updated: 2022/12/07 14:25:38 by fsnelder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "libft.h"
#include "util.h"
#include <assert.h> //TODO: REMOVE

typedef struct s_expander
{
	const char	*src;
	const char	*end;
	const char	**envp;
	t_string	result;
}	t_expander;

static void	expander_init(
		t_expander *expander, const char *src, size_t len, const char **envp)
{
	expander->src = src;
	expander->end = src + len;
	expander->envp = envp;
	// TODO: set initial capacity to len
	expander->result = string_new(0);
}

void	expand_character(t_expander *expander)
{
	string_push_back(&expander->result, *expander->src);
	expander->src++;
}

#define ALPHABETIC "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define UNDESCORE "_"
#define NUMBER "1234567890"
#define WORD_START "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define WORD_ENTRY "1234567890_abcdefghijklm\
nopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

/*
<variable> = "$" ( <word> | "?" )
<word> = "_" | ALPHA <word_character>*
<word_character> = "_" | ALPHA | NUMERIC
*/

const char	*ft_getenv(const char *begin, const char *end, const char **envp)
{
	size_t	len;

	len = end - begin;
	while (envp != NULL)
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

void	expand_exit_code(t_expander *expander)
{
	char	*code;

	// TODO: handle real exit code
	code = malloc_check(ft_itoa(0));
	string_push_str(&expander->result, code, code + ft_strlen(code));
	free(code);
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

typedef void	(*t_expander_function)(t_expander *);

static void	expand_dispatch(t_expander *expander)
{
	static const t_expander_function	expanders[255] = {
		['$'] = expand_variable,
		['\''] = expand_single_quote,
		['"'] = expand_double_quote
	};
	int									ch;

	ch = (unsigned int)*expander->src;
	if (expanders[ch] == NULL)
		expand_character(expander);
	else
		(expanders[ch])(expander);
}

t_string	expand_word(const char *src, size_t len, const char **envp)
{
	t_expander	expander;

	expander_init(&expander, src, len, envp);
	while (expander.src != expander.end)
	{
		expand_dispatch(&expander);
	}
	return (expander.result);
}
