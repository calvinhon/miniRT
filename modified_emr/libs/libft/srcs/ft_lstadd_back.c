/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:41:18 by nth          #+#    #+#             */
/*   Updated: 2023/11/10 20:57:46 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*dummy;

	if (!lst)
		return ;
	if (*lst)
	{
		dummy = *lst;
		while (dummy->next)
			dummy = dummy->next;
		dummy->next = new;
	}
	else
		*lst = new;
}
