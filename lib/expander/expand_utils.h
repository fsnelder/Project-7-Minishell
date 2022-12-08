/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 09:38:08 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/08 09:45:34 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_UTILS_H
# define EXPAND_UTILS_H

# define ALPHABETIC "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define UNDESCORE "_"
# define NUMBER "1234567890"
# define WORD_START "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define WORD_ENTRY "1234567890_abcdefghijklm\
nopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

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

#endif