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

/*
//
static t_mat4d	rt_get_cam_inverse(const t_mat4d *view)
{
	t_mat4d	ret;

	ret.matrix[0] = view->matrix[0];
	ret.matrix[1] = view->matrix[4];
	ret.matrix[2] = view->matrix[8];
	ret.matrix[4] = view->matrix[1];
	ret.matrix[5] = view->matrix[5];
	ret.matrix[6] = view->matrix[9];
	ret.matrix[8] = view->matrix[2];
	ret.matrix[9] = view->matrix[6];
	ret.matrix[10] = view->matrix[10];
	ret.matrix[3] = -(view->matrix[0] * view->matrix[3] + view->matrix[4]
			* view->matrix[7] + view->matrix[8] * view->matrix[11]);
	ret.matrix[7] = -(view->matrix[1] * view->matrix[3] + view->matrix[5]
			* view->matrix[7] + view->matrix[9] * view->matrix[11]);
	ret.matrix[11] = -(view->matrix[2] * view->matrix[3] + view->matrix[6]
			* view->matrix[7] + view->matrix[10] * view->matrix[11]);
	ret.matrix[12] = 0.0f;
	ret.matrix[13] = 0.0f;
	ret.matrix[14] = 0.0f;
	ret.matrix[15] = 1.0f;
	return (ret);
}
//
static void	cross_mat4d_mat4d(const t_mat4d in1,
						const t_mat4d in2, t_mat4d *out)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			out->matrix[4 * i + j] = in1.matrix[4 * i] * in2.matrix[j] + \
				in1.matrix[4 * i + 1] * in2.matrix[4 + j] + \
				in1.matrix[4 * i + 2] * in2.matrix[8 + j] + \
				in1.matrix[4 * i + 3] * in2.matrix[12 + j];
			j++;
		}
		i++;
	}
}
*/
//

void update_camera_state(t_camera *camera)
{
	normalize_vec4d(&camera->up);
	normalize_vec4d(&camera->left);
	normalize_vec4d(&camera->forward);
	camera->inv_transform = fill_matrix(
		create_vec4d(camera->left.x, camera->left.y, camera->left.z),
		create_vec4d(camera->up.x, camera->up.y, camera->up.z),
		create_vec4d(-camera->forward.x, -camera->forward.y,
					 -camera->forward.z),
		create_vec4d(0.0f, 0.0f, 0.0f));
	camera->inv_transform.matrix[15] = 1;
// added
	t_mat4d translate_m = translation_mat(-camera->from.x, -camera->from.y, -camera->from.z);
	camera->inv_transform = mult_n_mat4d(2, &translate_m, &camera->inv_transform);
	camera->inv_transform = inverse_mat4d(&camera->inv_transform);

/*
	cross_mat4d_mat4d(camera->inv_transform, \
		translation_mat(-camera->from.x, \
		-camera->from.y, -camera->from.z), &camera->inv_transform);
	camera->inv_transform = rt_get_cam_inverse(&camera->inv_transform);
*/

//
	printf("update camera\n");
}

static inline void _rotcam_apply_pitch_rot(t_minirt *state, bool left)
{
	const float angle = (PITCH_SPEED + MOVE_SPEED / 10.f) * state->delta_time;
	t_mat4d rot;

	if (left)
		rot = rotate_mat_y(-angle);
	else
		rot = rotate_mat_y(angle);
	state->cam.forward = mult_mat4d_vec4d(&rot, &state->cam.forward);
	state->cam.left = mult_mat4d_vec4d(&rot, &state->cam.left);
	state->cam.up = mult_mat4d_vec4d(&rot, &state->cam.up);
}

static inline void _rotcam_apply_yaw_rot(t_minirt *state, bool up)
{
	const float angle = (YAW_SPEED + MOVE_SPEED / 10.f) * state->delta_time;
	t_mat4d rot;

	if (up)
		rot = rt_rotation_matrix_from_axis_angle(&state->cam.left, angle);
	else
		rot = rt_rotation_matrix_from_axis_angle(&state->cam.left, -angle);
	state->cam.forward = mult_mat4d_vec4d(&rot, &state->cam.forward);
	state->cam.left = mult_mat4d_vec4d(&rot, &state->cam.left);
	state->cam.up = mult_mat4d_vec4d(&rot, &state->cam.up);
}

void camera_rotations(t_minirt *state)
{
	bool state_changed;

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
	//
	state->changed = state_changed;
}
