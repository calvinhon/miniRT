/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:45:28 by nth          #+#    #+#             */
/*   Updated: 2023/11/09 06:45:42 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*self;
	char	*dummy;

	self = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!self)
		return (NULL);
	dummy = self;
	while (*str)
		*dummy++ = *((char *)str++);
	*dummy = 0;
	return (self);
}
