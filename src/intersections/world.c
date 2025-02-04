/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:55:53 by chon              #+#    #+#             */
/*   Updated: 2025/01/30 17:55:53 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void normal_at(t_itx *itx, t_comps *comps)
{
	if (itx->obj->type == SPHERE)
		comps->normal_v = sphere_normal_at(itx->obj, &comps->p);
	else if (itx->obj->type == PLANE)
		comps->normal_v = plane_normal_at(itx->obj, &comps->p);
	else if (itx->obj->type == CYLINDER)
		comps->normal_v = cylinder_normal_at(itx->obj, &comps->p);
	else if (itx->obj->type == CUBE)
		comps->normal_v = cube_normal_at(itx->obj, &comps->p);
	else if (itx->obj->type == CONE)
		comps->normal_v = cone_normal_at(itx->obj, &comps->p);
	if (dot_pointers(&comps->normal_v, &comps->eye_v) < EPSILON)
		comps->normal_v = negate_vector(&comps->normal_v);
}

t_itx_grp	intersect(t_scene *s, t_ray *r)
{
	t_itx_grp	xs;
	int			i;

	i = -1;
	xs.count = 0;
	while (++i < s->num_shapes)
	{
		if (s->shapes[i].type == PLANE && xs.count + 1 <= MAX_ITX)
			intersect_plane(r, &s->shapes[i], &xs);
		else if (s->shapes[i].type == CONE && xs.count + 4 <= MAX_ITX)
			intersect_cone(r, &s->shapes[i], &xs);
		else if (xs.count + 2 <= MAX_ITX)
		{
			if (s->shapes[i].type == SPHERE)
				intersect_sphere(r, &s->shapes[i], &xs);
			else if (s->shapes[i].type == CYLINDER)
				intersect_cylinder(r, &s->shapes[i], &xs);
			else if (s->shapes[i].type == CUBE)
				intersect_cube(r, &s->shapes[i], &xs);
		}
	}
	return (xs);
}
