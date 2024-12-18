/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   322parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:32:20 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/19 00:35:50 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/minirt.h"

void	*allocate_obj(t_minirt *minirt, t_objtype type, size_t idx)
{
	minirt->scene.objs[idx].type = type;
	switch (type)
	{
		case SPHERE:
			minirt->scene.objs[idx].data = malloc(sizeof(t_sphere));
			break;
		case PLANE:
			minirt->scene.objs[idx].data = malloc(sizeof(t_plane));
			break;
		case CYLINDER:
			minirt->scene.objs[idx].data = malloc(sizeof(t_cylinder));
			break;
		case CUBE:
			minirt->scene.objs[idx].data = malloc(sizeof(t_cube));
			break;
		case CONE:
			minirt->scene.objs[idx].data = malloc(sizeof(t_cone));
			break;
		default:
			errors(ER_OBJ_TYPE, minirt);
	}
	if (!minirt->scene.objs[idx].data)
		errors(ER_MALLOC, minirt);
	return (minirt->scene.objs[idx].data);
}

void	parse_plane(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_plane	*plane;

	plane = (t_plane*) allocate_obj(minirt, PLANE, idx);
	(*i) += 2;
	plane->point = parse_point(data, i);
	plane->normal = parse_vector(data, i);
	plane->color = parse_color(data, i);
	#if BONUS
		// Bonus mode: Enable extra properties
		minirt->scene.objs[idx].reflection = parse_float(data, i);
		minirt->scene.objs[idx].shininess = parse_float(data, i);
	#endif
}

void	parse_sphere(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_sphere	*sphere;

	sphere = (t_sphere*) allocate_obj(minirt, SPHERE, idx);
	(*i) += 2;
	sphere->center = parse_point(data, i);
	sphere->radius = parse_float(data, i);
	sphere->color = parse_color(data, i);
	#if BONUS
		// Bonus mode: Enable extra properties
		minirt->scene.objs[idx].reflection = parse_float(data, i);
		minirt->scene.objs[idx].shininess = parse_float(data, i);
	#endif
}

void	parse_cylinder(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder*) allocate_obj(minirt, CYLINDER, idx);
	(*i) += 2;
	cylinder->base = parse_point(data, i);
	//
	printf("base = %f, %f, %f\n", cylinder->base.x, cylinder->base.y, cylinder->base.z);
	//
	cylinder->axis = parse_vector(data, i);
	cylinder->radius = parse_float(data, i);
	cylinder->height = parse_float(data, i);
	cylinder->color = parse_color(data, i);
	#if BONUS
		// Bonus mode: Enable extra properties
		minirt->scene.objs[idx].reflection = parse_float(data, i);
		minirt->scene.objs[idx].shininess = parse_float(data, i);
	#endif
	//
	
	//
}

void	parse_cone(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_cone	*cone;

	cone = (t_cone*) allocate_obj(minirt, CONE, idx);
	(*i) += 2;
	cone->apex = parse_point(data, i);
	cone->axis = parse_vector(data, i);
	cone->angle = parse_float(data, i);
	cone->color = parse_color(data, i);
	#if BONUS
		// Bonus mode: Enable extra properties
		minirt->scene.objs[idx].reflection = parse_float(data, i);
		minirt->scene.objs[idx].shininess = parse_float(data, i);
	#endif
}

void	parse_cube(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_cube	*cube;

	cube = (t_cube*) allocate_obj(minirt, CUBE, idx);
	(*i) += 2;
	cube->center = parse_point(data, i);
	cube->size = parse_float(data, i);
	cube->rotation = parse_vector(data, i);	
	cube->color = parse_color(data, i);
	#if BONUS
		// Bonus mode: Enable extra properties
		minirt->scene.objs[idx].reflection = parse_float(data, i);
		minirt->scene.objs[idx].shininess = parse_float(data, i);
	#endif
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
	//
	printf("BONUS = %d\n", BONUS);
	printf("objects[%ld].type = %i\n", idx, minirt->scene.objs[idx].type);// test
	printf("objects[%ld].brightness = %f\n", idx, minirt->scene.objs[idx].reflection);// test
	//
}

