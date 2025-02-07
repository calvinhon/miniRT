/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:18:05 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 17:31:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_camera_state(t_camera *camera)
{
	t_mat4d	translate_m;

	normalize_vec4d(&camera->up);
	normalize_vec4d(&camera->left);
	normalize_vec4d(&camera->forward);
	camera->inv_transform = fill_matrix(\
		create_vec4d(camera->left.x, camera->left.y, camera->left.z), \
		create_vec4d(camera->up.x, camera->up.y, camera->up.z), \
		create_vec4d(-camera->forward.x, -camera->forward.y, \
			-camera->forward.z), \
		create_vec4d(0.0f, 0.0f, 0.0f));
	camera->inv_transform.matrix[15] = 1;
	translate_m = translation_mat(-camera->from.x, -camera->from.y, \
		-camera->from.z);
	camera->inv_transform = mult_n_mat4d(2, &translate_m, &camera->inv_transform);
	camera->inv_transform = rt_get_cam_inverse(&camera->inv_transform);
	printf("update camera\n");
}

static inline void	_movecam_sideways_check(t_minirt *minirt, \
	bool *state_changed)
{
	t_vec4d	scaled_left;

	scale_vector(&scaled_left, &minirt->cam.left, \
		(MOVE_SPEED + (MOVE_SPEED / 2.f)) * minirt->delta_time);
	if (minirt->move.a)
	{
		minirt->cam.from = add_v_to_p(&minirt->cam.from, &scaled_left);
		*state_changed = true;
	}
	if (minirt->move.d)
	{
		minirt->cam.from = subtract_v_from_p(&minirt->cam.from, &scaled_left);
		*state_changed = true;
	}
}

static inline void	_movecam_longitudinally_check(t_minirt *minirt,
												bool *state_changed)
{
	t_vec4d	scaled_forward;

	scale_vector(&scaled_forward, &minirt->cam.forward, \
		(MOVE_SPEED + (MOVE_SPEED / 2.f)) * minirt->delta_time);
	if (minirt->move.w)
	{
		minirt->cam.from = add_v_to_p(&minirt->cam.from, &scaled_forward);
		*state_changed = true;
	}
	if (minirt->move.s)
	{
		minirt->cam.from = subtract_v_from_p(&minirt->cam.from, \
			&scaled_forward);
		*state_changed = true;
	}
}

static inline void	_movecam_elevation_check(t_minirt *minirt,
											bool *state_changed)
{
	if (minirt->move.space)
	{
		minirt->cam.from.y += (MOVE_SPEED * minirt->delta_time);
		*state_changed = true;
	}
	if (minirt->move.leftshift)
	{
		minirt->cam.from.y -= (MOVE_SPEED * minirt->delta_time);
		*state_changed = true;
	}
}

void	camera_controls(t_minirt *minirt)
{
	bool	state_changed;

	state_changed = false;
	_movecam_sideways_check(minirt, &state_changed);
	_movecam_longitudinally_check(minirt, &state_changed);
	_movecam_elevation_check(minirt, &state_changed);
	if (state_changed)
		update_camera_state(&minirt->cam);
	minirt->changed = minirt->changed || state_changed;
}
