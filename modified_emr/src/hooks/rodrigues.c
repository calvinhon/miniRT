/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rodrigues.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:51:23 by nth          #+#    #+#             */
/*   Updated: 2024/11/19 20:03:36 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline t_vec4s	compute_rot_row(t_vec4s k, int row, float angle)
{
	const float	sin_theta = sinf(angle);
	const float	cos_theta = cosf(angle);
	const float	one_minus_cos = 1.f - cos_theta;

	if (row == 1)
		return (vec4s_re(\
			cos_theta + k.x * k.x * one_minus_cos, \
			k.x * k.y * one_minus_cos - k.z * sin_theta, \
			k.x * k.z * one_minus_cos + k.y * sin_theta, \
			0.0f));
	if (row == 2)
		return (vec4s_re(\
			k.x * k.y * one_minus_cos + k.z * sin_theta, \
			cos_theta + k.y * k.y * one_minus_cos, \
			k.y * k.z * one_minus_cos - k.x * sin_theta, \
			0.0f));
	return (vec4s_re(\
		k.x * k.z * one_minus_cos - k.y * sin_theta, \
		k.y * k.z * one_minus_cos + k.x * sin_theta, \
		cos_theta + k.z * k.z * one_minus_cos, \
		0.0f));
}

t_mat4s	rt_rotation_matrix_from_axis_angle(const t_vec4s *axis, float angle)
{
	t_mat4s	rot;
	t_vec4s	k;

	k = normalize_vec4s_re(*axis);
	rot.r1 = compute_rot_row(k, 1, angle);
	rot.r2 = compute_rot_row(k, 2, angle);
	rot.r3 = compute_rot_row(k, 3, angle);
	rot.r4 = vec4s_re(0.0f, 0.0f, 0.0f, 1.0f);
	return (rot);
}
