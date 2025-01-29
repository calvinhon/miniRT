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

void	update_camera_state(t_camera *camera)
{
	camera->up = normalize(camera->up);
	camera->left = normalize(camera->left);
	camera->forward = normalize(camera->forward);
	camera->inv_transform = fill_matrix(
		create_vec4d(camera->left.x, camera->left.y, camera->left.z), 
		create_vec4d(camera->up.x, camera->up.y, camera->up.z), 
		create_vec4d(-camera->forward.x, -camera->forward.y, 
			-camera->forward.z), 
		create_vec4d(0.0f, 0.0f, 0.0f) 
	);
	camera->inv_transform.matrix[15] = 1;
	//camera->inv_transform = mult_n_mat4d(2, camera->inv_transform, 
	//	translation_mat(-camera->from.x, -camera->from.y, -camera->from.z));
	//camera->inv_transform = inverse_mat4d(camera->inv_transform);
	////
	//plane->rot = rt_extract_rot_vertical(plane->orientation);
	//plane->inv_transform = mult_n_mat4d(3, plane->rot, plane->scale, plane->translate);	
	//plane->inv_transform = inverse_mat4d(plane->inv_transform);
	////
	printf("update camera\n");
}

static inline void	_rotcam_apply_pitch_rot(t_minirt *state, bool left)
{
	const float	angle = (PITCH_SPEED + MOVE_SPEED / 10.f) * state->delta_time;
	t_mat4d		rot;

	if (left)
		rot = rotate_mat_y(-angle);
	else
		rot = rotate_mat_y(angle);
	state->cam.forward = mult_mat4d_vec4d(rot, state->cam.forward);
	state->cam.left = mult_mat4d_vec4d(rot, state->cam.left);
	state->cam.up = mult_mat4d_vec4d(rot, state->cam.up);
}

static inline void	_rotcam_apply_yaw_rot(t_minirt *state, bool up)
{
	const float	angle = (YAW_SPEED + MOVE_SPEED / 10.f) * state->delta_time;
	t_mat4d		rot;

	if (up)
		rot = rt_rotation_matrix_from_axis_angle(&state->cam.left, angle);
	else
		rot = rt_rotation_matrix_from_axis_angle(&state->cam.left, -angle);
	state->cam.forward = mult_mat4d_vec4d(rot, state->cam.forward);
	state->cam.left = mult_mat4d_vec4d(rot, state->cam.left);
	state->cam.up = mult_mat4d_vec4d(rot, state->cam.up);
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
