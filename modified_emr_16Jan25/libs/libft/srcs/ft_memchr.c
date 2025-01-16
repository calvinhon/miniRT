/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:43:11 by nth          #+#    #+#             */
/*   Updated: 2023/11/08 13:53:17 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*self;

	self = (unsigned char *)s;
	while (n--)
	{
		if (*self == (unsigned char)c)
			return ((void *)self);
		self++;
	}
	return (NULL);
}
