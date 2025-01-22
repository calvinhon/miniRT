/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:22:29 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 18:40:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

void	parse_shape(t_minirt *minirt, char *data, size_t *i)
{
	size_t	start;
	size_t	idx;

	idx = minirt->scene.shape_count++;
	start = *i;
	if (data[start] == 'p' && data[start + 1] == 'l' && data[start + 2] == ' ')
		parse_plane(minirt, data, i, idx);
	else if (data[start] == 's' && data[start + 1] == 'p' && data[start + 2] == ' ')
		parse_sphere(minirt, data, i, idx);
	else if (data[start] == 'c' && data[start + 1] == 'y' && data[start + 2] == ' ')
		parse_cylinder(minirt, data, i, idx);
	else if (data[start] == 'c' && data[start + 1] == 'u' && data[start + 2] == ' ')
		parse_cube(minirt, data, i, idx);
	else if (data[start] == 'c' && data[start + 1] == 'o' && data[start + 2] == ' ')
		parse_cone(minirt, data, i, idx);
	else
	{
		ft_printf("Unknown object type: %c%c at position %d\n", data[start], data[start + 1], start);
		errors(CER_OBJ_TYPE,ER_OBJ_TYPE, minirt);
	}
		
}

void	parse_data(t_minirt *minirt, char *data)
{
	size_t	i;

	i = 0;
	while (data[i])
	{
		while (data[i] == '\t' || data[i] == ' ' || data[i] == '\n')
			i++;
		if (!data[i])
			break ;
		if (data[i] == 'A'  && data[i + 1] == ' ')
			parse_ambient(minirt, data, &i);
		else if (data[i] == 'C' && data[i + 1] == ' ')
			parse_camera(minirt, data, &i);
		else if ((data[i] == 'L' || data[i] == 'l') && data[i + 1] == ' ')
			parse_light(minirt, data, &i);
		else if ((data[i] == 'S' || data[i] == 's') && (data[i + 1] == 'L'|| data[i + 1] == 'l')
		 && data[i + 2] == ' ')
			parse_spotlight(minirt, data, &i);
		else
			parse_shape(minirt, data, &i);
	}
}
