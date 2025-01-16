/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:39:49 by nth          #+#    #+#             */
/*   Updated: 2024/11/18 15:26:08 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

t_vec4s	sphere_normal_at(t_object *sphere, t_vec4s *world_p)
{
	t_vec4s	local_p;
	t_vec4s	local_n;
	t_vec4s	world_n;
	t_vec2s	uv;
	t_vec4s	tangent;

	cross_mat4s_vec4s(&sphere->inv_transform, world_p, &local_p);
	sub_vec4s(&local_n, &local_p, &sphere->trans);
	if (sphere->material.fra_tex)
	{
		sub_vec4s(&local_p, &local_p, &sphere->trans);
		uv = rt_get_sphere_uv_local(&local_p);
		tangent = rt_get_sphere_tangent(&local_n);
		world_n = rt_apply_normal_map(sphere, &uv, &local_n, &tangent);
		cross_mat4s_vec4s(&sphere->transposed_inverse, &world_n, &world_n);
	}
	else
		cross_mat4s_vec4s(&sphere->transposed_inverse, &local_n, &world_n);
	world_n.w = 0.f;
	normalize_vec4s(&world_n);
	return (world_n);
}

bool	intersect_sphere(t_ray *r, t_object *sphere, t_itx_grp *xs)
{
	float	d;
	t_ray	trans_r;
	t_vec4s	sphere_to_ray;
	t_vec4s	abc;

	if (xs->count + 2 >= _RT_MAX_ITX)
		return (false);
	trans_r = *r;
	ray_transform(&trans_r, &sphere->inv_transform);
	sub_vec4s(&sphere_to_ray, &trans_r.origin, &sphere->trans);
	abc.x = dot_vec4s_re(&trans_r.direction, &trans_r.direction);
	abc.y = 2.0f * dot_vec4s_re(&sphere_to_ray, &trans_r.direction);
	abc.z = dot_vec4s_re(&sphere_to_ray, &sphere_to_ray) - 1.f;
	d = abc.y * abc.y - 4.f * abc.x * abc.z;
	if (d < 0)
		return (false);
	d = sqrtf(d);
	xs->arr[xs->count].object = sphere;
	xs->arr[xs->count++].t = (-abc.y - d) / (2.f * abc.x);
	xs->arr[xs->count].object = sphere;
	xs->arr[xs->count++].t = (-abc.y + d) / (2.f * abc.x);
	return (true);
}
