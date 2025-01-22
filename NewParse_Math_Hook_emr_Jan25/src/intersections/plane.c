/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:48:39 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 18:39:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

t_vec4s	plane_normal_at(t_object *plane, t_vec4s *world_p)
{
	t_vec4s	world_n;
	t_vec2s	uv;
	t_vec4s	tangent;

	if (plane->material.fra_tex)
	{
		tangent = rt_get_plane_tangent(&plane->orientation);
		uv = rt_get_plane_uv_local(world_p, tangent, &plane->orientation);
		world_n = rt_apply_normal_map(plane, &uv, &plane->orientation,
				&tangent);
		return (world_n);
	}
	return (plane->orientation);
}

bool	intersect_plane(t_ray *ray, t_object *plane, t_itx_grp *xs)
{
	t_ray		trans_ray;
	float		denom;
	float		t;

	trans_ray = *ray;
	ray_transform(&trans_ray, &plane->inv_transform);
	if (fabsf(trans_ray.direction.y) < EPSILON)
		return (false);
	denom = trans_ray.direction.y;
	t = -trans_ray.origin.y / denom;
	if (t > EPSILON)
	{
		xs->arr[xs->count].object = plane;
		xs->arr[xs->count++].t = t;
		return (true);
	}
	return (false);
}
