/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 15:04:04 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/09 10:37:30 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	ft_pwd(const char **args, const char **envp);
int	ft_cd(const char **args, const char **envp);
int	ft_echo(const char **args, const char **envp);
int	ft_env(const char **args, const char **envp);
int	ft_exit(const char **args, const char **envp);
int	ft_export(const char **args, const char **envp);
int	ft_unset(const char **args, const char **envp);

#endif
