/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:57:56 by nth          #+#    #+#             */
/*   Updated: 2024/09/23 12:16:53 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

t_vec4s	cylinder_normal_at(t_object *cy, t_vec4s *world_point)
{
	t_vec4s	local_point;
	t_vec4s	local_normal;
	t_vec4s	world_normal;

	cross_mat4s_vec4s(&cy->inv_transform, world_point, &local_point);
	if (fabsf(local_point.y - 1.f) < EPSILON)
		vec4sv_ini(&local_normal, 0, 1, 0);
	else if (fabsf(local_point.y + 1.f) < EPSILON)
		vec4sv_ini(&local_normal, 0, -1, 0);
	else
		vec4sv_ini(&local_normal, local_point.x, 0, local_point.z);
	cross_mat4s_vec4s(&cy->transposed_inverse,
		&local_normal, &world_normal);
	world_normal.w = 0;
	normalize_vec4s(&world_normal);
	return (world_normal);
}

static inline float	cy_discriminant(t_ray *ray, t_object *cy,
						float *t_values, t_itx_grp *xs)
{
	t_vec4s		oc;
	float		a;
	float		b;
	float		c;
	float		y0;

	oc = ray->origin;
	cy->center.w = 1.f;
	(void)xs;
	sub_vec4s(&oc, &oc, &cy->center);
	a = ray->direction.x * ray->direction.x + ray->direction.z * ray->direction.z;
	if (fabsf(a) < EPSILON && cy->specs.closed)
		return (-1);
	b = 2 * (oc.x * ray->direction.x + oc.z * ray->direction.z);
	c = oc.x * oc.x + oc.z * oc.z - 1.f;
	t_values[0] = (-b - sqrt(b * b - 4.f * a * c)) / (2.f * a);
	t_values[1] = (-b + sqrt(b * b - 4.f * a * c)) / (2.f * a);
	y0 = oc.y + t_values[0] * ray->direction.y;
	if (y0 < -1.f || y0 > 1.f)
		t_values[0] = -1.f;
	y0 = oc.y + t_values[1] * ray->direction.y;
	if (y0 < -1.f || y0 > 1.f)
		t_values[1] = -1.f;
	return (b * b - 4.f * a * c);
}

bool	intersect_cylinder(t_ray *ray, t_object *cy, t_itx_grp *xs)
{
	float	disc;
	float	t_values[2];
	t_ray	transformed_ray;
	bool	itx_occured;

	transformed_ray = *ray;
	ray_transform(&transformed_ray, &(cy->inv_transform));
	disc = cy_discriminant(&transformed_ray, cy, t_values, xs);
	itx_occured = false;
	if (disc < EPSILON || (t_values[0] < EPSILON && t_values[1] < EPSILON))
		return (false);
	if (t_values[0] >= EPSILON)
	{
		xs->arr[xs->count].object = cy;
		xs->arr[xs->count++].t = t_values[0];
		itx_occured = true;
	}
	if (t_values[1] >= EPSILON)
	{
		xs->arr[xs->count].object = cy;
		xs->arr[xs->count++].t = t_values[1];
		itx_occured = true;
	}
	return (itx_occured);
}
