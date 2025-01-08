/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   321parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:32:20 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/25 15:26:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	parse_bonus(t_minirt *minirt, char *data, \
				size_t *i, size_t idx)
{
	minirt->scene.objs[idx].reflection = parse_float(data, i);
	minirt->scene.objs[idx].shininess = parse_float(data, i);
}

void	*allocate_obj(t_minirt *minirt, t_objtype type, size_t idx)
{
	minirt->scene.objs[idx].type = type;
	if (type == SPHERE)
		minirt->scene.objs[idx].data = malloc(sizeof(t_sphere));
	else if (type == PLANE)
		minirt->scene.objs[idx].data = malloc(sizeof(t_plane));
	else if (type == CYLINDER)
		minirt->scene.objs[idx].data = malloc(sizeof(t_cylinder));
	else if (type == CUBE)
		minirt->scene.objs[idx].data = malloc(sizeof(t_cube));
	else if (type == CONE)
		minirt->scene.objs[idx].data = malloc(sizeof(t_cone));
	else
		errors(ER_OBJ_TYPE, minirt);
	if (!minirt->scene.objs[idx].data)
		errors(ER_MALLOC, minirt);
	return (minirt->scene.objs[idx].data);
}

void	parse_plane(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_plane	*plane;

	plane = (t_plane *)allocate_obj(minirt, PLANE, idx);
	(*i) += 2;
	plane->point = parse_point(data, i);
	plane->normal = parse_vector(data, i);
	plane->color = parse_color(data, i);
	if (BONUS)
		parse_bonus(minirt, data, i, idx);
}

void	parse_sphere(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)allocate_obj(minirt, SPHERE, idx);
	(*i) += 2;
	sphere->center = parse_point(data, i);
	sphere->radius = parse_float(data, i);
	sphere->color = parse_color(data, i);
	if (BONUS)
		parse_bonus(minirt, data, i, idx);
}

void	parse_cylinder(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)allocate_obj(minirt, CYLINDER, idx);
	(*i) += 2;
	cylinder->base = parse_point(data, i);
	cylinder->axis = parse_vector(data, i);
	cylinder->radius = parse_float(data, i);
	cylinder->height = parse_float(data, i);
	cylinder->color = parse_color(data, i);
	if (BONUS)
		parse_bonus(minirt, data, i, idx);
}
