/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:41:36 by nth          #+#    #+#             */
/*   Updated: 2023/11/07 11:29:53 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;

	if (!del || !lst || !(*lst))
		return ;
	while (*lst)
	{
		curr = *lst;
		*lst = curr->next;
		ft_lstdelone(curr, del);
	}
	*lst = NULL;
}
