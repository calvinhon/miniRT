/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parametrizations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:00:42 by nth          #+#    #+#             */
/*   Updated: 2024/11/19 14:43:07 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec2d	rt_get_sphere_uv_local(t_vec4d *hitp)
{
	const float	two_pi = 2.f * (float)PI;
	t_vec2d		uv;
	float		phi;
	float		theta;
	t_vec4d		op_hitp;

	op_hitp = *hitp;
	phi = atan2f(hitp->z, hitp->x);
	theta = acosf(hitp->y / magnitude(&op_hitp));
	if (phi < 0.f)
		phi += two_pi;
	if (theta < 0.f)
		theta += (float)PI;
	uv.x = phi / two_pi;
	if (uv.x >= 1.f)
		uv.x = 0.999f;
	uv.y = theta / (float)PI;
	if (uv.y >= 1.f)
		uv.y = 0.999f;
	return (uv);
}

t_vec2d	rt_get_plane_uv_local(t_vec4d *hitp, t_vec4d tangent, t_vec4d *normal)
{
	t_vec4d	bitangent;
	t_vec2d	uv;
	float	tile_factor;

	tile_factor = 0.1f;
	bitangent = cross_pointers(&tangent, normal);
	uv.x = dot_pointers(hitp, &tangent) * tile_factor;
	uv.y = dot_pointers(hitp, &bitangent) * tile_factor;
	uv.x = uv.x - floorf(uv.x);
	uv.y = uv.y - floorf(uv.y);
	return (uv);
}
