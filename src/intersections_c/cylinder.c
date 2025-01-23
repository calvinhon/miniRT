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

	// printf("world: %f %f %f\n", wrld_p->x, wrld_p->y, wrld_p->z);
	obj_pt = mult_mat4d_pt4d(o->inv_transform, *wrld_p);
	// printf("obj: %f\n", wrld_p->y);
	dist = pow(obj_pt.x, 2) + pow(obj_pt.z, 2);
	// printf("%f\t", dist);
	// printf("maxy: %f, miny: %f\n", o->specs.t_cyl.max_y - EPSILON, o->specs.t_cyl.min_y + EPSILON);
	// printf("obj y:%f\t", obj_pt.y);
	if (dist < 1 && obj_pt.y >= o->specs.t_cyl.max_y - EPSILON)
	{
		// printf("hits\n");
		obj_normal = create_vec4d(0, 1, 0);
	}
	else if (dist < 1 && obj_pt.y <= o->specs.t_cyl.min_y + EPSILON)
	{
		// printf("hits\n");
		obj_normal = create_vec4d(0, -1, 0);
	}
	else
		obj_normal = create_vec4d(obj_pt.x, 0, obj_pt.z);
	// printf("%f %f %f\t", obj_normal.x, obj_normal.y, obj_normal.z);
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
	// printf("Cap check: x=%f, z=%f, t=%f\n", x, z, t);
	// printf("%f\t", x * x + z * z);
	return (x * x + z * z <= 1 + EPSILON);
}

void intersect_caps(t_ray *r, t_object *o, t_itx_set *xs)
{
	float	t;

	if (!o->specs.t_cyl.closed || fabsf(r->direction.y) < EPSILON)
		return ;
	t = (o->specs.t_cyl.min_y - r->origin.y) / r->direction.y;
	// printf("t: %f direction.y: %f\n", t, r->direction.y);
	if (check_cap(r, t))
	{
		// printf("lower cap\n");
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t;
	}
	t = (o->specs.t_cyl.max_y - r->origin.y) / r->direction.y;
	if (check_cap(r, t))
	{
		// printf("upper cap\n");
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
	// printf("min y: %f max y: %f\n", o->specs.t_cyl.min_y, o->specs.t_cyl.max_y);
	if (y > o->specs.t_cyl.min_y
		&& y < o->specs.t_cyl.max_y)
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t[0];
		// printf("wall_1\n");
	}
	y = r->origin.y + t[1] * r->direction.y;
	// printf("y: %f\n", y);
	if (y > o->specs.t_cyl.min_y
		&& y < o->specs.t_cyl.max_y)
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t[1];
		// printf("wall_2\n");
	}
}

void intersect_cylinder(t_ray *r, t_object *o, t_itx_set *xs)
{
	t_ray trfm_r;
	// t_vec4d o_to_ray;
	t_vec4d abc;
	float d;
	float t[3];

	trfm_r = *r;
	transform_ray(&trfm_r, &o->inv_transform);
	intersect_caps(&trfm_r, o, xs);
	// o_to_ray = subtract_points(trfm_r.origin, o->center);
	// o_to_ray = create_vec4d(trfm_r.origin.x, trfm_r.origin.y, trfm_r.origin.z);
	abc.x = pow(trfm_r.direction.x, 2) + pow(trfm_r.direction.z, 2);
	if (abc.x < EPSILON)
		return ;
	abc.y = 2 * trfm_r.origin.x * trfm_r.direction.x + 2 * trfm_r.origin.z * trfm_r.direction.z;
	abc.z = pow(trfm_r.origin.x, 2) + pow(trfm_r.origin.z, 2) - 1;
	d = abc.y * abc.y - 4 * abc.x * abc.z;
	if (d < 0)
		return ;
	d = sqrtf(d);
	abc.x *= 2.f;
	t[0] = (-abc.y - d) / abc.x;
	t[1] = (-abc.y + d) / abc.x;
	check_y_values(t, &trfm_r, o, xs);
}
