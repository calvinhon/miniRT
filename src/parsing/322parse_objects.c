/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   322parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:32:20 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/17 19:39:14 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


#include "minirt.h"


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
	if (BONUS)
	{
		minirt->scene.objs[idx].reflection = parse_float(data, i);
		minirt->scene.objs[idx].shininess = parse_float(data, i);
	}
}


void	parse_object(t_minirt *minirt, char *data, int *i)
{
	size_t	start;
	size_t	idx;

	idx = minirt->scene.idx_obj++;
	start = *i;
	if (data[start] == 'p' && data[start + 1] == 'l')
		parse_plane(minirt, data, &i, idx);
	else if (data[start] == 's' && data[start + 1] == 'p')
		parse_sphere(minirt, data, &i, idx);
	else if (data[start] == 'c' && data[start + 1] == 'y')
		parse_cylinder(minirt, data, &i, idx);
	else if (data[start] == 'c' && data[start + 1] == 'u')
		parse_cubic(minirt, data, &i, idx);
	else if (data[start] == 'c' && data[start + 1] == 'o')
		parse_cone(minirt, data, &i, idx);
	else
		errors(ER_INVALID_OBJECT, minirt);
}

