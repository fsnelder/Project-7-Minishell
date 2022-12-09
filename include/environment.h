/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 11:03:34 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 11:47:06 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_environment {
	char	**envp;
	size_t	cap;
	size_t	len;
}	t_environment;

t_environment	environment_init(const char **envp);
void			environment_destroy(t_environment *env);
void			environment_set(t_environment *env,
					const char *name, const char *value);
void			environment_swap_remove(t_environment *env, const char *name);
const char		*environment_get(t_environment *env, const char *name);
bool			is_valid_identifier(const char *name);

#endif
