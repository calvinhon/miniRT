/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:52:37 by marvin            #+#    #+#             */
/*   Updated: 2024/12/11 16:52:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	parse(t_minirt *minirt, char *file)
{
	char	*data;
	size_t	total_size;

	data = NULL;
	total_size = 0;
	data = file_data(minirt, &total_size, file);
	ft_printf("%d \n", total_size); //
	if (!data || total_size == 0)
	{
		free(data);
		errors(ER_EMPTY_MAP, minirt);
	}
	//
	write(1, data, total_size);
	//
	// parse_data(minirt, data);
	free(data);
}
