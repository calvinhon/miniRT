/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:50:33 by chon              #+#    #+#             */
/*   Updated: 2025/01/20 16:50:33 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4d sphere_normal_at(t_object *o, t_point *wrld_p)
{
	t_point obj_pt;
	t_vec4d obj_normal;
	t_vec4d wrld_normal;
	t_mat4d transposed;

	obj_pt = mult_mat4d_pt4d(&o->inv_transform, wrld_p);
	// obj_normal = subtract_points(&obj_pt, create_point(0, 0, 0));
	obj_normal = create_vec4d(obj_pt.x, obj_pt.y, obj_pt.z);
	transposed = transpose_mat4d(&o->inv_transform);
	wrld_normal = mult_mat4d_vec4d(&transposed, &obj_normal);
	wrld_normal = normalize(&wrld_normal);
	return (wrld_normal);
}

void intersect_sphere(t_ray *r, t_object *o, t_itx_grp *xs)
{
	t_ray trfm_r;
	t_vec4d o_to_ray;
	t_vec4d abc;
	float d;

	trfm_r = *r;
	transform_ray(&trfm_r, &o->inv_transform);
	// o_to_ray = subtract_points(trfm_r.origin, o->center);
	o_to_ray = create_vec4d(trfm_r.origin.x, trfm_r.origin.y, trfm_r.origin.z);
	abc.x = dot_pointers(&trfm_r.direction, &trfm_r.direction);
	abc.y = 2.f * dot_pointers(&trfm_r.direction, &o_to_ray);
	abc.z = dot_pointers(&o_to_ray, &o_to_ray) - 1.f;
	d = abc.y * abc.y - 4.f * abc.x * abc.z;
	if (d < 0)
		return;
	d = sqrtf(d);
	abc.x *= 2.f;
	xs->arr[xs->count].obj = o;
	xs->arr[xs->count++].t = (-abc.y - d) / abc.x;
	xs->arr[xs->count].obj = o;
	xs->arr[xs->count++].t = (-abc.y + d) / abc.x;
}
