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

static inline void	_movecam_sideways_check(t_minirt *state,
						bool *state_changed)
{
	t_vec4s	scaled_left;

	scale_vec4s(&scaled_left, state->cam.left, \
		(MOVE_SPEED + (MOVE_SPEED / 2.f)) * state->delta_time);
	if (state->move.a)
	{
		add_vec4s(&state->cam.trans, &scaled_left, &state->cam.trans);
		*state_changed = true;
	}
	if (state->move.d)
	{
		sub_vec4s(&state->cam.trans, &state->cam.trans, &scaled_left);
		*state_changed = true;
	}
}

static inline void	_movecam_longitudinally_check(t_minirt *state,
						bool *state_changed)
{
	t_vec4s	scaled_forward;

	scale_vec4s(&scaled_forward, state->cam.forward, \
		(MOVE_SPEED + (MOVE_SPEED / 2.f)) * state->delta_time);
	if (state->move.w)
	{
		add_vec4s(&state->cam.trans, &scaled_forward, &state->cam.trans);
		*state_changed = true;
	}
	if (state->move.s)
	{
		sub_vec4s(&state->cam.trans, &state->cam.trans, &scaled_forward);
		*state_changed = true;
	}
}

static inline void	_movecam_elevation_check(t_minirt *state,
						bool *state_changed)
{
	if (state->move.space)
	{
		state->cam.trans.y += (MOVE_SPEED * state->delta_time);
		*state_changed = true;
	}
	if (state->move.leftshift)
	{
		state->cam.trans.y -= (MOVE_SPEED * state->delta_time);
		*state_changed = true;
	}
}

void	camera_controls(t_minirt *state)
{
	bool	state_changed;

	state_changed = false;
	if (state->move.a || state->move.d || state->move.s
		|| state->move.w || state->move.space || state->move.leftshift)
	{
		_movecam_sideways_check(state, &state_changed);
		_movecam_longitudinally_check(state, &state_changed);
		_movecam_elevation_check(state, &state_changed);
		if (state_changed)
			update_camera_state(&state->cam);
	}
}
