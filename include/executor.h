/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 15:17:15 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/08 10:28:44 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "libft.h"

typedef struct s_executor
{
	int		*pids;
	t_list	*commands;
	size_t	ncommands;
}	t_executor;

int	execute(t_list *commands);

#endif
