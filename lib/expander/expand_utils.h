/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 09:38:08 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 11:44:59 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_UTILS_H
# define EXPAND_UTILS_H

# include "grammar.h"

typedef struct s_expander
{
	const char	*src;
	const char	*end;
	const char	**envp;
	t_string	result;
}	t_expander;

void	expand_character(t_expander *expander);
void	expand_exit_code(t_expander *expander);
void	expand_variable(t_expander *expander);
void	expand_single_quote(t_expander *expander);
void	expand_double_quote(t_expander *expander);

void	expand_environment_variable(t_expander *expander);

void	expander_init(t_expander *expander,
			const char *src, size_t len, const char **envp);
void	expand_dispatch(t_expander *expander, const char *to_expand);

#endif