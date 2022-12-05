/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 13:44:50 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/05 13:44:51 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fsnelder <fsnelder@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 13:44:50 by fsnelder      #+#    #+#                 */
/*   Updated: 2022/12/05 13:44:51 by fsnelder      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{	
	t_list	*last;

	if (lst == NULL)
		return ;
	if (!(*lst))
		(*lst) = new;
	else
	{
		last = ft_lstlast(*lst);
		last -> next = new;
	}
}
