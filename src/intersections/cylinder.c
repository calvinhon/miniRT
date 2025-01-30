/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:35:57 by chon              #+#    #+#             */
/*   Updated: 2025/01/30 18:38:42 by chon             ###   ########.fr       */
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
	dist = pow(obj_p.x, 2) + pow(obj_p.z, 2);
	if (dist < 1 && obj_p.y >= o->specs.max_y - EPSILON)
		obj_normal = create_vec4d(0, 1, 0);
	else if (dist < 1 && obj_p.y <= o->specs.min_y + EPSILON)
		obj_normal = create_vec4d(0, -1, 0);
	else
		obj_normal = create_vec4d(obj_p.x, 0, obj_p.z);
	transposed = transpose_mat4d(&o->inv_transform);
	wrld_normal = mult_mat4d_vec4d(&transposed, &obj_normal);
	return (normalize(&wrld_normal));
}

float check_cap(t_ray *r, float t)
{
	float x;
	float z;

	x = r->origin.x + t * r->direction.x;
	z = r->origin.z + t * r->direction.z;
	return (x * x + z * z <= 1 + EPSILON);
}

void intersect_caps(t_ray *r, t_object *o, t_itx_grp *xs)
{
	float t;

	if (!o->specs.closed || fabsf(r->direction.y) < EPSILON)
		return;
	t = (o->specs.min_y - r->origin.y) / r->direction.y;
	if (check_cap(r, t))
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t;
	}
	t = (o->specs.max_y - r->origin.y) / r->direction.y;
	if (check_cap(r, t))
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t;
	}
}

void check_y_values(float *t, t_ray *r, t_object *o, t_itx_grp *xs)
{
	float y;

	swap(t);
	y = r->origin.y + t[0] * r->direction.y;
	if (y > o->specs.min_y && y < o->specs.max_y)
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t[0];
	}
	y = r->origin.y + t[1] * r->direction.y;
	if (y > o->specs.min_y && y < o->specs.max_y)
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t[1];
	}
}

void intersect_cylinder(t_ray *r, t_object *o, t_itx_grp *xs)
{
	t_ray trfm_r;
	t_vec4d abc;
	float d;
	float t[3];

	trfm_r = *r;
	transform_ray(&trfm_r, &o->inv_transform);
	intersect_caps(&trfm_r, o, xs);
	abc.x = pow(trfm_r.direction.x, 2) + pow(trfm_r.direction.z, 2);
	if (abc.x < EPSILON)
		return;
	abc.y = 2 * trfm_r.origin.x * trfm_r.direction.x + 2 * trfm_r.origin.z * trfm_r.direction.z;
	abc.z = pow(trfm_r.origin.x, 2) + pow(trfm_r.origin.z, 2) - 1;
	d = abc.y * abc.y - 4 * abc.x * abc.z;
	if (d < 0)
		return;
	d = sqrtf(d);
	abc.x *= 2.f;
	t[0] = (-abc.y - d) / abc.x;
	t[1] = (-abc.y + d) / abc.x;
	check_y_values(t, &trfm_r, o, xs);
}
