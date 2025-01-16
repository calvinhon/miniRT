/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:27:30 by nth          #+#    #+#             */
/*   Updated: 2024/02/02 18:32:21 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*self;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		content = (*f)(lst->content);
		self = ft_lstnew(content);
		if (!self)
		{
			ft_lstclear(&head, del);
			(*del)(content);
			return (NULL);
		}
		ft_lstadd_back(&head, self);
		lst = lst->next;
	}
	return (head);
}
