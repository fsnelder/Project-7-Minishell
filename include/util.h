/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 14:17:34 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/06 11:30:01 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stddef.h>

typedef enum e_result
{
	SUCCESS = 0,
	GENERAL_ERROR
}	t_result;

void	*ft_malloc(size_t n);
void	*malloc_check(void *ptr);
void	*ft_malloc(size_t n);

#endif
