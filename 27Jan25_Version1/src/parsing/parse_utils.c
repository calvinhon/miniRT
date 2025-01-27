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

t_vec4s	parse_point(char *data, size_t *i)
{
	t_vec4s	point;

	point.x = parse_float(data, i);
	point.y = parse_float(data, i);
	point.z = parse_float(data, i);
	point.w = 1.0;
	return (point);
}

t_vec4s	parse_vector(char *data, size_t *i)
{
	t_vec4s	vector;

	vector.x = parse_float(data, i);
	vector.y = parse_float(data, i);
	vector.z = parse_float(data, i);
	vector.w = 0.0;
	return (vector);
}

void	parse_shape(t_minirt *minirt, char *data, size_t *i)
{
	size_t	idx;

	idx = minirt->scene.shape_count++;
	if (data[*i] == 'p' && data[*i + 1] == 'l' \
		&& data[*i + 2] == ' ')
		parse_plane(minirt, data, i, idx);
	else if (data[*i] == 's' && data[*i + 1] == 'p' \
		&& data[*i + 2] == ' ')
		parse_sphere(minirt, data, i, idx);
	else if (data[*i] == 'c' && data[*i + 1] == 'y' \
		&& data[*i + 2] == ' ')
		parse_cylinder(minirt, data, i, idx);
	else if (data[*i] == 'c' && data[*i + 1] == 'u' \
		&& data[*i + 2] == ' ')
		parse_cube(minirt, data, i, idx);
	else if (data[*i] == 'c' && data[*i + 1] == 'o' \
		&& data[*i + 2] == ' ')
		parse_cone(minirt, data, i, idx);
	else
	{
		ft_printf("Unknown object type: %c%c at position %d\n", \
			data[*i], data[*i + 1], *i);
		errors(CER_OBJ_TYPE, ER_OBJ_TYPE, minirt);
	}
}

void	parse_data(t_minirt *minirt, char *data, size_t total_size)
{
	size_t	i;

	i = 0;
	while (data[i])
	{
		while (data[i] == '\t' || data[i] == ' ' || data[i] == '\n')
			i++;
		if (!data[i])
			break ;
		if (data[i] == 'A' && data[i + 1] == ' ')
			parse_ambient(minirt, data, &i);
		else if (data[i] == 'C' && data[i + 1] == ' ')
			parse_camera(minirt, data, &i);
		else if ((data[i] == 'L' || data[i] == 'l') && data[i + 1] == ' ')
			parse_light(minirt, data, &i);
		else if ((data[i] == 'S' || data[i] == 's') && (data[i + 1] == 'L' \
			|| data[i + 1] == 'l') && data[i + 2] == ' ')
			parse_spotlight(minirt, data, &i);
		else
			parse_shape(minirt, data, &i);
	}
	if (i == total_size)
		ft_printf("Parsing completed successfully\n");
	else
		ft_printf("Parsing failed at position %ld\n", i);
}
