/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:33:36 by chon              #+#    #+#             */
/*   Updated: 2024/12/16 18:46:25 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (ft_strlen(s) == 0)
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
			i++;
		count++;
	}
	if (s[i - 1] == c)
		return (count - 1);
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		str_ct;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	str_ct = str_count(s, c);
	array = malloc((str_ct + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (str_ct > 0)
	{
		while (s[j] == c)
			j++;
		array[i++] = ft_substr(s, j, ft_strchr(s + j, c) - (s + j));
		if (ft_strchr(s + j, c) == NULL)
			break ;
		j += ft_strchr(s + j, c) - (s + j);
		str_ct--;
	}
	array[i] = NULL;
	return (array);
}
