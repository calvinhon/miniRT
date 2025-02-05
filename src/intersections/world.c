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

float	check_cap(t_ray *r, float t, float radius)
{
	float	x;
	float	z;

	x = r->origin.x + t * r->direction.x;
	z = r->origin.z + t * r->direction.z;
	return (x * x + z * z <= radius + EPSILON);
}

void	intersect_caps(t_ray *r, t_object *o, t_itx_grp *xs, bool is_cone)
{
	float	t;
	float	radius;

	if (!o->specs.closed || fabsf(r->direction.y) < EPSILON)
		return ;
	if (is_cone)
		radius = fabsf(o->specs.min_y);
	else
		radius = 1.f;
	if (is_cone)
		t = (o->specs.min_y - r->origin.y) / r->direction.y;
	else
		t = (-1.0f - r->origin.y) / r->direction.y;
	if (check_cap(r, t, radius))
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t;
	}
	if (is_cone)
		radius = fabsf(o->specs.max_y);
	if (is_cone)
		t = (o->specs.max_y - r->origin.y) / r->direction.y;
	else
		t = (1.f - r->origin.y) / r->direction.y;
	if (check_cap(r, t, radius))
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t;
	}
}

void	check_y_values(float *t, t_ray *r, t_object *o, t_itx_grp *xs)
{
	float	y;

	swap(t);
	y = r->origin.y + t[0] * r->direction.y;
	if (y > -1.0f && y < 1.0f)
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t[0];
	}
	y = r->origin.y + t[1] * r->direction.y;
	if (y > -1.0f && y < 1.0f)
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t[1];
	}
}

//void	check_y_values(float *t, t_ray *r, t_object *o, t_itx_grp *xs)
//{
//	float	y;

//	swap(t);
//	y = r->origin.y + t[0] * r->direction.y;
//	if (y > o->specs.min_y && y < o->specs.max_y)
//	{
//		xs->arr[xs->count].obj = o;
//		xs->arr[xs->count++].t = t[0];
//	}
//	y = r->origin.y + t[1] * r->direction.y;
//	if (y > o->specs.min_y && y < o->specs.max_y)
//	{
//		xs->arr[xs->count].obj = o;
//		xs->arr[xs->count++].t = t[1];
//	}
//}

void	swap(float *t)
{
	if (t[0] > t[1])
	{
		t[2] = t[0];
		t[0] = t[1];
		t[1] = t[2];
	}
}

t_itx_grp	local_intersect(t_scene *s, t_ray *r)
{
	t_itx_grp	xs;
	int			i;

	i = -1;
	xs.count = 0;
	while (++i < s->num_shapes)
	{
		if (s->shapes[i].type == SPHERE && xs.count + 2 <= MAX_ITX)
			intersect_sphere(r, &s->shapes[i], &xs);
		else if (s->shapes[i].type == PLANE && xs.count + 1 <= MAX_ITX)
			intersect_plane(r, &s->shapes[i], &xs);
		else if (s->shapes[i].type == CYLINDER && xs.count + 2 <= MAX_ITX)
			intersect_cylinder(r, &s->shapes[i], &xs);
		else if (s->shapes[i].type == CUBE && xs.count + 2 <= MAX_ITX)
			intersect_cube(r, &s->shapes[i], &xs);
		else if (s->shapes[i].type == CONE && xs.count + 2 <= MAX_ITX)
			intersect_cone(r, &s->shapes[i], &xs);
	}
	return (xs);
}
