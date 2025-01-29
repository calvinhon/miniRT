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

static inline void	_movecam_sideways_check(t_minirt *state,
						bool *state_changed)
{
	t_vec4d	scaled_left;

	scaled_left = scale_vector(&state->cam.left,
		(MOVE_SPEED + (MOVE_SPEED / 2.f)) * state->delta_time);
	if (state->move.a)
	{
		state->cam.from = add_v_to_p(state->cam.from, scaled_left);
		*state_changed = true;
	}
	if (state->move.d)
	{
		state->cam.from = subtract_v_from_p(state->cam.from, scaled_left);
		*state_changed = true;
	}
}

static inline void	_movecam_longitudinally_check(t_minirt *state,
						bool *state_changed)
{
	t_vec4d	scaled_forward;

	scaled_forward = scale_vector(&state->cam.forward,
		(MOVE_SPEED + (MOVE_SPEED / 2.f)) * state->delta_time);
	if (state->move.w)
	{
		state->cam.from = add_v_to_p(state->cam.from, scaled_forward);
		*state_changed = true;
	}
	if (state->move.s)
	{
		state->cam.from = subtract_v_from_p(state->cam.from, scaled_forward);
		*state_changed = true;
	}
}

static inline void	_movecam_elevation_check(t_minirt *state,
						bool *state_changed)
{
	if (state->move.space)
	{
		state->cam.from.y += (MOVE_SPEED * state->delta_time);
		*state_changed = true;
	}
	if (state->move.leftshift)
	{
		state->cam.from.y -= (MOVE_SPEED * state->delta_time);
		*state_changed = true;
	}
}

void	camera_controls(t_minirt *state)
{
	bool	state_changed;

	state_changed = false;
	_movecam_sideways_check(state, &state_changed);
	_movecam_longitudinally_check(state, &state_changed);
	_movecam_elevation_check(state, &state_changed);
	if (state_changed)
		update_camera_state(&state->cam);
}
