/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:57:01 by chon              #+#    #+#             */
/*   Updated: 2025/01/22 15:50:04 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec4d plane_normal_at(t_object *o, t_point *wrld_p)
{
	t_vec4d obj_normal;
	t_vec4d wrld_normal;
	t_mat4d transposed;
	// t_vec4d	world_n;
	// t_vec2d	uv;
	// t_vec4d	tangent;

	// if (plane->material.tex)
	// {
	// 	tangent = rt_get_plane_tangent(&plane->orientation);
	// 	uv = rt_get_plane_uv_local(world_p, tangent, &plane->orientation);
	// 	world_n = rt_apply_normal_map(plane, &uv, &plane->orientation,
	// 			&tangent);
	// 	return (world_n);
	// }
	// return (plane->orientation);
	(void)o;
	(void)wrld_p;
	obj_normal = create_vec4d(0, 1, 0);
	transposed = transpose_mat4d(o->inv_transform);
	wrld_normal = mult_mat4d_vec4d(transposed, obj_normal);
	return (normalize(&wrld_normal));
}

void intersect_plane(t_ray *r, t_object *o, t_itx_grp *xs)
{
	t_ray trans_r;
	float t;

	if (xs->count + 1 >= MAX_ITX)
		return ;
	trans_r = *r;
	transform_ray(&trans_r, &o->inv_transform);
	t = (-trans_r.origin.y + EPSILON) / trans_r.direction.y;
	if (xs->count + 1 >= MAX_ITX || fabs(trans_r.direction.y) < EPSILON)
		return ;
	xs->arr[xs->count].obj = o;
	xs->arr[xs->count++].t = t;
}