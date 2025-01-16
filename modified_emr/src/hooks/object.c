/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:18:38 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 17:31:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

static inline void	update_object_cache(t_object *object)
{
	object->inv_transform = get_inv_tranform_mat4s(\
	object->rot, 
	object->scale, \
	object->trans \
	);
	transpose_mat4s(&object->inv_transform, &object->transposed_inverse);
}

static inline void	_move_sideways_check(t_minirt *state, bool *state_changed)
{
	t_object	*selected_object;
	t_vec4s	scaled_left;

	scale_vec4s(&scaled_left, state->cam.left,
		(MOVE_SPEED + (MOVE_SPEED / 2.f)) * state->delta_time);
	selected_object = state->selected.object;
	if (state->move.a)
	{
		add_vec4s(&selected_object->trans, &selected_object->trans,
			&scaled_left);
		*state_changed = true;
	}
	if (state->move.d)
	{
		sub_vec4s(&selected_object->trans, &selected_object->trans,
			&scaled_left);
		*state_changed = true;
	}
}

static inline void	_move_longitudinally_check(t_minirt *state,
						bool *state_changed)
{
	t_object	*selected_object;
	t_vec4s		viewport_forward;
	t_vec4s		op;

	selected_object = state->selected.object;
	op = vec4s_re(selected_object->trans.x, \
		state->cam.trans.y, selected_object->trans.z, 1);
	sub_vec4s(&viewport_forward, &op, &state->cam.trans);
	viewport_forward.w = 0.f;
	normalize_vec4s(&viewport_forward);
	scale_vec4s(&viewport_forward, viewport_forward,
		(MOVE_SPEED + (MOVE_SPEED / 2.f)) * state->delta_time);
	if (state->move.w)
	{
		add_vec4s(&selected_object->trans, &selected_object->trans,
			&viewport_forward);
		*state_changed = true;
	}
	if (state->move.s)
	{
		sub_vec4s(&selected_object->trans, &selected_object->trans,
			&viewport_forward);
		*state_changed = true;
	}
}

static inline void	_move_elevation_check(t_minirt *state, bool *state_changed)
{
	t_object	*selected_object;

	selected_object = state->selected.object;
	if (state->move.space)
	{
		selected_object->trans.y += (MOVE_SPEED * state->delta_time);
		*state_changed = true;
	}
	if (state->move.leftshift)
	{
		selected_object->trans.y -= (MOVE_SPEED * state->delta_time);
		*state_changed = true;
	}
}

void	object_controls(t_minirt *state)
{
	t_object	*selected_object;
	bool	state_changed;

	state_changed = false;
	selected_object = state->selected.object;
	_move_sideways_check(state, &state_changed);
	_move_longitudinally_check(state, &state_changed);
	_move_elevation_check(state, &state_changed);
	if (state_changed)
		update_object_cache(selected_object);
}
