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

#include "miniRT.h"

static inline void	update_camera_state(t_camera *camera)
{
	normalize_vec4s(&camera->up);
	normalize_vec4s(&camera->left);
	normalize_vec4s(&camera->forward);
	camera->inv_transform = inirows_mat4s_re(\
		vec4s_re(camera->left.x, camera->left.y, camera->left.z, 0.0f), \
		vec4s_re(camera->up.x, camera->up.y, camera->up.z, 0.0f), \
		vec4s_re(-camera->forward.x, -camera->forward.y, \
			-camera->forward.z, 0.0f), \
		vec4s_re(0.0f, 0.0f, 0.0f, 1.0f) \
	);
	cross_mat4s_mat4s(camera->inv_transform, \
		translation_mat4s(\
			-camera->trans.x, -camera->trans.y, -camera->trans.z \
		), \
			&camera->inv_transform \
		);
	camera->inv_transform = rt_get_cam_inverse(&camera->inv_transform);
}

static inline void	_rotcam_apply_pitch_rot(t_minirt *state, bool left)
{
	const float	angle = (PITCH_SPEED + MOVE_SPEED / 10.f) * state->delta_time;
	t_mat4s		rot;

	if (left)
		rot = rotatey_mat4s(-angle);
	else
		rot = rotatey_mat4s(angle);
	cross_mat4s_vec4s(&rot, &state->cam.forward, &state->cam.forward);
	cross_mat4s_vec4s(&rot, &state->cam.left, &state->cam.left);
	cross_mat4s_vec4s(&rot, &state->cam.up, &state->cam.up);
}

static inline void	_rotcam_apply_yaw_rot(t_minirt *state, bool up)
{
	const float	angle = (YAW_SPEED + MOVE_SPEED / 10.f) * state->delta_time;
	t_mat4s		rot;

	if (up)
		rot = rt_rotation_matrix_from_axis_angle(&state->cam.left, angle);
	else
		rot = rt_rotation_matrix_from_axis_angle(&state->cam.left, -angle);
	cross_mat4s_vec4s(&rot, &state->cam.forward, &state->cam.forward);
	cross_mat4s_vec4s(&rot, &state->cam.left, &state->cam.left);
	cross_mat4s_vec4s(&rot, &state->cam.up, &state->cam.up);
}

void	camera_rotations(t_minirt *state)
{
	bool	state_changed;

	if (state->move.left == true)
	{
		_rotcam_apply_pitch_rot(state, true);
		state_changed = true;
	}
	if (state->move.right == true)
	{
		_rotcam_apply_pitch_rot(state, false);
		state_changed = true;
	}
	if (state->move.up == true)
	{
		_rotcam_apply_yaw_rot(state, true);
		state_changed = true;
	}
	if (state->move.down == true)
	{
		_rotcam_apply_yaw_rot(state, false);
		state_changed = true;
	}
	if (state_changed)
		update_camera_state(&state->cam);
}
