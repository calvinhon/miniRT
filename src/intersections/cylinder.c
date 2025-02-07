/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:35:57 by chon              #+#    #+#             */
/*   Updated: 2025/02/05 09:59:06 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4d cylinder_normal_at(t_object *o, t_point *wrld_p)
{
	t_point obj_p;
	t_vec4d obj_normal;
	t_mat4d transposed;
	t_vec4d wrld_normal;
	float dist;

	obj_p = mult_mat4d_pt4d(&o->inv_transform, wrld_p);
	dist = obj_p.x * obj_p.x + obj_p.z * obj_p.z;
	if (dist < 1 && obj_p.y >= 1.0f - EPSILON) // specs.max_y
		obj_normal = create_vec4d(0, 1, 0);
	else if (dist < 1 && obj_p.y <= -1.0f + EPSILON)
		obj_normal = create_vec4d(0, -1, 0); //o->specs.min_y
	else
		obj_normal = create_vec4d(obj_p.x, 0, obj_p.z);
	transposed = transpose_mat4d(&o->inv_transform);
	wrld_normal = mult_mat4d_vec4d(&transposed, &obj_normal);
	return (normalize(&wrld_normal));
}

void intersect_cylinder(t_ray *r, t_object *o, t_itx_grp *xs)
{
	t_ray trfm_r;
	t_vec4d abc;
	float d;
	float t[3];

	trfm_r = *r;
	transform_ray(&trfm_r, &o->inv_transform);
	intersect_caps(&trfm_r, o, xs, 0);
	abc.x = trfm_r.direction.x * trfm_r.direction.x + trfm_r.direction.z * trfm_r.direction.z;
	if (abc.x < EPSILON)
		return ;
	abc.y = 2 * (trfm_r.origin.x * trfm_r.direction.x + \
		trfm_r.origin.z * trfm_r.direction.z);
	abc.z = trfm_r.origin.x * trfm_r.origin.x + trfm_r.origin.z * trfm_r.origin.z - 1;
	d = abc.y * abc.y - 4 * abc.x * abc.z;
	if (d < -EPSILON)
		return;
	if (d > 0)
		d = sqrtf(d);
	abc.x *= 2.f;
	t[0] = (-abc.y - d) / abc.x;
	t[1] = (-abc.y + d) / abc.x;
	check_y_values(t, &trfm_r, o, xs, false);
}
