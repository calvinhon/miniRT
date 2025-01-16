/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:39:55 by nth          #+#    #+#             */
/*   Updated: 2023/11/10 21:14:56 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t n)
{
	void	*self;
	size_t	total_size;

	if (!nmemb || !n)
	{
		nmemb = 1;
		n = 1;
	}
	if (nmemb > SIZE_MAX / n)
		return (NULL);
	total_size = n * nmemb;
	self = malloc(total_size);
	if (!self)
		return (NULL);
	ft_bzero(self, total_size);
	return (self);
}
