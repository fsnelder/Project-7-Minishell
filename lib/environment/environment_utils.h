/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment_utils.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 11:11:31 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 11:33:21 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_UTILS_H
# define ENVIRONMENT_UTILS_H

void	environment_resize(t_environment *env);
int		environment_get_index(t_environment *env, const char *name);
void	environment_push_back(t_environment *env,
			const char *name, const char *value);
void	environment_replace(t_environment *env,
			const char *name, const char *value, int index);

extern char	**environ;

#endif
