/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 14:17:34 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 11:39:23 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stddef.h>
# include "environment.h"

typedef struct s_minishell_data {
	int				exit_code;
	t_environment	env;
}	t_minishell_data;

extern t_minishell_data	g_ms_data;

typedef enum e_result
{
	SUCCESS = 0,
	GENERAL_ERROR,
	COMMAND_NOT_EXECUTABLE = 126,
	COMMAND_NOT_FOUND = 127,
	SIGNAL_CODE = 128
}	t_result;

void	*ft_malloc(size_t n);
void	*malloc_check(void *ptr);
void	*ft_malloc(size_t n);
void	init_minishell(void);

extern char				**environ;

#endif
