/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:38:22 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 17:31:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


static inline void _rotcam_apply_pitch_rot(t_minirt *minirt, bool left)
{
	const float angle = (PITCH_SPEED + MOVE_SPEED / 10.f) * minirt->delta_time;
	t_mat4d rot;

	if (left)
		rot = rotate_mat_y(-angle);
	else
		rot = rotate_mat_y(angle);
	minirt->cam.forward = mult_mat4d_vec4d(&rot, &minirt->cam.forward);
	minirt->cam.left = mult_mat4d_vec4d(&rot, &minirt->cam.left);
	minirt->cam.up = mult_mat4d_vec4d(&rot, &minirt->cam.up);
}

static inline void _rotcam_apply_yaw_rot(t_minirt *minirt, bool up)
{
	const float angle = (YAW_SPEED + MOVE_SPEED / 10.f) * minirt->delta_time;
	t_mat4d rot;

	if (up)
		rot = rt_rotation_matrix_from_axis_angle(&minirt->cam.left, angle);
	else
		rot = rt_rotation_matrix_from_axis_angle(&minirt->cam.left, -angle);
	minirt->cam.forward = mult_mat4d_vec4d(&rot, &minirt->cam.forward);
	minirt->cam.left = mult_mat4d_vec4d(&rot, &minirt->cam.left);
	minirt->cam.up = mult_mat4d_vec4d(&rot, &minirt->cam.up);
}

void camera_rotations(t_minirt *minirt)
{
	bool state_changed;

	state_changed = false;
	
	if (minirt->move.left == true)
	{
		_rotcam_apply_pitch_rot(minirt, true);
		state_changed = true;
	}
	if (minirt->move.right == true)
	{
		_rotcam_apply_pitch_rot(minirt, false);
		state_changed = true;
	}
	if (minirt->move.up == true)
	{
		_rotcam_apply_yaw_rot(minirt, true);
		state_changed = true;
	}
	if (minirt->move.down == true)
	{
		_rotcam_apply_yaw_rot(minirt, false);
		state_changed = true;
	}
	if (state_changed)
		update_camera_state(&minirt->cam);
	//
	minirt->changed = minirt->changed || state_changed;
}
