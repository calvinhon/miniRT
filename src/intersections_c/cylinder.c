/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:35:57 by chon              #+#    #+#             */
/*   Updated: 2025/01/23 13:35:10 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4d cylinder_normal_at(t_object *o, t_point *wrld_p)
{
	t_point obj_pt;
	t_vec4d obj_normal;
	t_vec4d wrld_normal;
	t_mat4d transposed;
	float	dist;

	dist = pow(wrld_p->x, 2) + pow(wrld_p->z, 2);
	if (dist < 1 && wrld_p->y >= o->specs.t_cyl.max_y - EPSILON)
		obj_normal = create_vec4d(0, 1, 0);
	else if (dist < 1 && wrld_p->y <= o->specs.t_cyl.min_y + EPSILON)
		obj_normal = create_vec4d(0, -1, 0);
	else
	{
		obj_pt = mult_mat4d_pt4d(o->inv_transform, *wrld_p);
		obj_normal = subtract_points(obj_pt, create_point(0, obj_pt.y, 0));
	}
	transposed = transpose_mat4d(o->inv_transform);
	wrld_normal = mult_mat4d_vec4d(transposed, obj_normal);
	return (normalize(wrld_normal));
}

float check_cap(t_ray *r, float t)
{
	float x;
	float z;

	x = r->origin.x + t * r->direction.x;
	z = r->origin.z + t * r->direction.z;
	return ((x * x + z * z) <= 1);
}

void intersect_caps(t_ray *r, t_object *o, t_itx_set *xs)
{
	float	t;

	if (!o->specs.t_cyl.closed || fabsf(r->direction.y) < EPSILON)
		return ;
	t = (o->specs.t_cyl.min_y - r->origin.y) / r->direction.y;
	if (check_cap(r, t))
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t;
	}
	t = (o->specs.t_cyl.max_y - r->origin.y) / r->direction.y;
	if (check_cap(r, t))
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t;
	}
}

void check_y_values(float *t, t_ray *r, t_object *o, t_itx_set *xs)
{
	float y;

	if (t[0] > t[1])
	{
		t[2] = t[0];
		t[0] = t[1];
		t[1] = t[2];
	}
	y = r->origin.y + t[0] * r->direction.y;
	if (y > o->specs.t_cyl.min_y + EPSILON
		&& y < o->specs.t_cyl.max_y - EPSILON)
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t[0];
	}
	y = r->origin.y + t[1] * r->direction.y;
	if (y > o->specs.t_cyl.min_y + EPSILON
		&& y < o->specs.t_cyl.max_y - EPSILON)
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t[1];
	}
}

void intersect_cylinder(t_ray *r, t_object *o, t_itx_set *xs)
{
	t_ray trfm_r;
	t_vec4d o_to_ray;
	t_vec4d abc;
	float d;
	float t[3];

	trfm_r = *r;
	transform_ray(&trfm_r, &o->inv_transform);
	// o_to_ray = subtract_points(trfm_r.origin, o->center);
	o_to_ray = create_vec4d(trfm_r.origin.x, trfm_r.origin.y, trfm_r.origin.z);
	abc.x = pow(trfm_r.direction.x, 2) + pow(trfm_r.direction.z, 2);
	if (abc.x < EPSILON)
		return (intersect_caps(&trfm_r, o, xs));
	abc.y = 2 * trfm_r.origin.x * trfm_r.direction.x + 2 * trfm_r.origin.z * trfm_r.direction.z;
	abc.z = pow(trfm_r.origin.x, 2) + pow(trfm_r.origin.z, 2) - 1;
	d = abc.y * abc.y - 4 * abc.x * abc.z;
	if (d < 0)
		return (intersect_caps(&trfm_r, o, xs));
	d = sqrtf(d);
	abc.x *= 2.f;
	t[0] = (-abc.y - d) / abc.x;
	t[1] = (-abc.y + d) / abc.x;
	check_y_values(t, &trfm_r, o, xs);
}
