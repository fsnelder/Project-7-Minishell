#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*temp;

	if (!lst)
		return (NULL);
	new_lst = NULL;
	while (lst -> next != NULL)
	{
		temp = ft_lstnew((*f)(lst -> content));
		if (temp == NULL)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, temp);
		lst = lst -> next;
	}
	temp = ft_lstnew(f(lst -> content));
	if (temp == NULL)
	{
		ft_lstclear(&new_lst, del);
		return (NULL);
	}
	ft_lstadd_back(&new_lst, temp);
	return (new_lst);
}
