/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   322parse_objects2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:32:20 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/21 14:37:05 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	parse_bonus(t_minirt *minirt, char *data, \
				size_t *i, size_t idx)
{
	minirt->scene.objs[idx].reflection = parse_float(data, i);
	minirt->scene.objs[idx].shininess = parse_float(data, i);
}

void	parse_cone(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_cone	*cone;

	cone = (t_cone *)allocate_obj(minirt, CONE, idx);
	(*i) += 2;
	cone->apex = parse_point(data, i);
	cone->axis = parse_vector(data, i);
	cone->angle = parse_float(data, i);
	cone->color = parse_color(data, i);
	if (BONUS)
		parse_bonus(minirt, data, i, idx);
}

void	parse_cube(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_cube	*cube;

	cube = (t_cube *) allocate_obj(minirt, CUBE, idx);
	(*i) += 2;
	cube->center = parse_point(data, i);
	cube->size = parse_float(data, i);
	cube->rotation = parse_vector(data, i);
	cube->color = parse_color(data, i);
	if (BONUS)
		parse_bonus(minirt, data, i, idx);
}

void	parse_object(t_minirt *minirt, char *data, size_t *i)
{
	size_t	start;
	size_t	idx;

	idx = minirt->scene.idx_obj++;
	start = *i;
	if (data[start] == 'p' && data[start + 1] == 'l')
		parse_plane(minirt, data, i, idx);
	else if (data[start] == 's' && data[start + 1] == 'p')
		parse_sphere(minirt, data, i, idx);
	else if (data[start] == 'c' && data[start + 1] == 'y')
		parse_cylinder(minirt, data, i, idx);
	else if (data[start] == 'c' && data[start + 1] == 'u')
		parse_cube(minirt, data, i, idx);
	else if (data[start] == 'c' && data[start + 1] == 'o')
		parse_cone(minirt, data, i, idx);
	else
		errors(ER_OBJ_TYPE, minirt);
}

