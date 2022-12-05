#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	temp = (*lst);
	if (!(*lst))
		return ;
	while ((*lst) != NULL)
	{
		(*lst) = (*lst)-> next;
		del ((temp)-> content);
		free (temp);
		temp = (*lst);
	}
	lst = NULL;
}
