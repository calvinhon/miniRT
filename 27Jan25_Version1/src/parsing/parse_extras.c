/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:51:45 by nth          #+#    #+#             */
/*   Updated: 2025/01/14 17:00:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"
#include "libft.h"
#include "minirt.h"

static inline t_vec4s	quat_from_axis_angle(const t_vec4s axis, float theta)
{
	t_vec4s		q;
	float		sin_half_theta;

	sin_half_theta = sinf(theta / 2);
	q.w = cosf(theta / 2);
	q.x = axis.x * sin_half_theta;
	q.y = axis.y * sin_half_theta;
	q.z = axis.z * sin_half_theta;
	return (q);
}

static inline t_mat4s	mat4_from_quat(const t_vec4s q)
{
	t_mat4s	ret;
	t_vec4s	x;
	t_vec4s	y;
	t_vec4s	z;
	t_vec4s	w;

	x.x = q.x * q.x;
	y.y = q.y * q.y;
	z.z = q.z * q.z;
	x.y = q.x * q.y;
	x.z = q.x * q.z;
	y.z = q.y * q.z;
	w.x = q.w * q.x;
	w.y = q.w * q.y;
	w.z = q.w * q.z;
	vec4sv_ini(&ret.r1, 1 - 2 * (y.y + z.z), 2 * (x.y - w.z), 2
		* (x.z + w.y));
	vec4sv_ini(&ret.r2, 2 * (x.y + w.z), 1 - 2 * (x.x + z.z), 2
		* (y.z - w.x));
	vec4sv_ini(&ret.r3, 2 * (x.z - w.y), 2 * (y.z + w.x), 1 - 2
		* (x.x + y.y));
	vec4sp_ini(&ret.r4, 0.f, 0.f, 0.f);
	return (ret);
}

t_mat4s	rt_extract_rot_vertical(const t_vec4s u)
{
	t_vec4s	j_hat;
	t_vec4s	rot_axis;
	float	theta;
	t_vec4s	q;

	j_hat = vec4sv_re(0.f, 1.f, 0.f);
	if (u.x == 0 && fabsf(u.y - 1) < EPSILON && u.z == 0)
		return (ini_indentity_mat4s());
	if (u.x == 0 && fabsf(u.y + 1) < EPSILON && u.z == 0)
		return (rotatex_mat4s((float)-M_PI));
	rot_axis = cross_vec4s_re(j_hat, u);
	if (magnitude_vec4s_re(rot_axis) < EPSILON)
		return (ini_indentity_mat4s());
	rot_axis = normalize_vec4s_highp(rot_axis);
	theta = acosf(fmaxf(-1.0f, fminf(1.0f, dot_vec4s_re(&u, &j_hat))));
	q = quat_from_axis_angle(rot_axis, theta);
	return (mat4_from_quat(q));
}

bool	is_normalised(t_vec4s *vec, size_t pos, t_minirt *minirt)
{
	float	mag;

	magnitude_vec4s(&mag, *vec);
	if (mag <= EPSILON)
	{
		printf("Zero vector as input at position %zu \n", pos);
		errors(CER_ZERO_VEC, ER_ZERO_VEC, minirt);
	}
	else if (fabsf(mag - 1.0f) > EPSILON)
	{
		printf("Unormalized vector at position %zu \
			has been normalised. \n", pos);
		*vec = normalize_vec4s_highp(*vec);
		return (false);
	}
	return (true);
}
