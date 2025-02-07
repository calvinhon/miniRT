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

#include "minirt.h"

static inline t_vec4d compute_rot_row(t_vec4d k, int row, float angle)
{
	const float sin_theta = sinf(angle);
	const float cos_theta = cosf(angle);
	const float one_minus_cos = 1.f - cos_theta;

	if (row == 0)
		return (create_vec4d(\
			cos_theta + k.x * k.x * one_minus_cos, \
			k.x * k.y * one_minus_cos - k.z * sin_theta, \
			k.x * k.z * one_minus_cos + k.y * sin_theta));
	if (row == 1)
		return (create_vec4d(
			k.x * k.y * one_minus_cos + k.z * sin_theta,
			cos_theta + k.y * k.y * one_minus_cos,
			k.y * k.z * one_minus_cos - k.x * sin_theta));
	return (create_vec4d(
		k.x * k.z * one_minus_cos - k.y * sin_theta,
		k.y * k.z * one_minus_cos + k.x * sin_theta,
		cos_theta + k.z * k.z * one_minus_cos));
}

t_mat4d rt_rotation_matrix_from_axis_angle(const t_vec4d *axis, float angle)
{
	t_mat4d rot;
	t_vec4d k;

	k = normalize(axis);
	rot = fill_matrix(compute_rot_row(k, 0, angle),
					  compute_rot_row(k, 1, angle),
					  compute_rot_row(k, 2, angle),
					  create_vec4d(0, 0, 0));
	rot.matrix[15] = 1;
	return (rot);
}
