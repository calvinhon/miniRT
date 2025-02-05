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

// #include "libft.h"
#include "minirt.h"

static inline t_vec4d quat_from_axis_angle(const t_vec4d axis, float theta)
{
	t_vec4d q;
	float sin_half_theta;

	sin_half_theta = sinf(theta / 2);
	q.p = cosf(theta / 2);
	q.x = axis.x * sin_half_theta;
	q.y = axis.y * sin_half_theta;
	q.z = axis.z * sin_half_theta;
	return (q);
}

static inline t_mat4d mat4_from_quat(const t_vec4d q)
{
	t_mat4d ret;
	t_vec4d x;
	t_vec4d y;
	t_vec4d z;
	t_vec4d p;

	x.x = q.x * q.x;
	x.y = q.x * q.y;
	x.z = q.x * q.z;
	y.y = q.y * q.y;
	y.z = q.y * q.z;
	z.z = q.z * q.z;
	p.x = q.p * q.x;
	p.y = q.p * q.y;
	p.z = q.p * q.z;
	fill_row(&ret, 0, create_vec4d(1 - 2 * (y.y + z.z), 2 * (x.y - p.z), 2 * (x.z + p.y)));
	fill_row(&ret, 1, create_vec4d(2 * (x.y + p.z), 1 - 2 * (x.x + z.z), 2 * (y.z - p.x)));
	fill_row(&ret, 2, create_vec4d(2 * (x.z - p.y), 2 * (y.z + p.x), 1 - 2 * (x.x + y.y)));
	fill_row(&ret, 3, create_vec4d(0, 0, 0));
	ret.matrix[15] = 1;
	return (ret);
}

t_mat4d rt_extract_rot_vertical(const t_vec4d u)
{
	t_vec4d j_hat;
	t_vec4d rot_axis;
	float theta;
	t_vec4d q;

	j_hat = create_vec4d(0.f, 1.f, 0.f);
	if (u.x == 0 && fabsf(u.y - 1) < EPSILON && u.z == 0)
		return (identity_mat());
	if (u.x == 0 && fabsf(u.y + 1) < EPSILON && u.z == 0)
		return (rotate_mat_x((float)-M_PI));
	rot_axis = cross_pointers(&j_hat, &u);
	if (magnitude(&rot_axis) < EPSILON)
		return (identity_mat());
	rot_axis = normalize(&rot_axis);
	theta = acosf(fmaxf(-1.0f, fminf(1.0f, dot_pointers(&u, &j_hat))));
	q = quat_from_axis_angle(rot_axis, theta);
	return (mat4_from_quat(q));
}

bool is_normalised(t_vec4d *vec, size_t pos, t_minirt *minirt)
{
	float mag;

	mag = magnitude(vec);
	if (mag <= EPSILON)
	{
		printf("Zero vector as input at position %zu \n", pos);
		errors(CER_ZERO_VEC, ER_ZERO_VEC, minirt);
	}
	else if (fabsf(mag - 1.0f) > EPSILON)
	{
		printf("Unnormalized vector at position %zu has been \
			normalised. \n",
			   pos);
		*vec = normalize(vec);
		return (false);
	}
	return (true);
}
