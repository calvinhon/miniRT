/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:35:57 by chon              #+#    #+#             */
/*   Updated: 2025/01/22 16:50:18 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4d cylinder_normal_at(t_object *o, t_point *wrld_p)
{
	t_point obj_pt;
	t_vec4d obj_normal;
	t_vec4d wrld_normal;
	t_mat4d transposed;

	obj_pt = mult_mat4d_pt4d(o->inv_transform, *wrld_p);
	obj_normal = subtract_points(obj_pt, create_point(0, obj_pt.y, 0));
	transposed = transpose_mat4d(o->inv_transform);
	wrld_normal = mult_mat4d_vec4d(transposed, obj_normal);
	normalize(wrld_normal);
	return (create_vec4d(wrld_normal.x, 0, wrld_normal.z));
}

void intersect_cylinder(t_ray *r, t_object *o, t_itx_set *xs)
{
	t_ray trans_r;
	t_vec4d o_to_ray;
	t_vec4d abc;
	float d;

	if (xs->count + 2 >= MAX_ITX)
		return ;
	trans_r = *r;
	transform_ray(&trans_r, &o->inv_transform);
	o_to_ray = subtract_points(trans_r.origin, o->center);
	abc.x = pow(trans_r.direction.x, 2) + pow(trans_r.direction.z, 2);
	if (abc.x < EPSILON)
		return ;
	abc.y = 2 * trans_r.origin.x * trans_r.direction.x
		+ 2 * trans_r.origin.z * trans_r.direction.z;
	abc.z = pow(trans_r.origin.x, 2) + pow(trans_r.origin.z, 2) - 1;
	d = abc.y * abc.y - 4 * abc.x * abc.z;
	if (d < 0)
		return ;
	d = sqrtf(d);
	abc.x *= 2.f;
	xs->arr[xs->count].obj = o;
	xs->arr[xs->count++].t = (-abc.y - d) / abc.x;
	xs->arr[xs->count].obj = o;
	xs->arr[xs->count++].t = (-abc.y + d) / abc.x;
}
