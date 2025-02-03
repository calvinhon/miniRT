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

#include "minirt.h"
#include "macros.h"

static inline void	update_object_cache(t_object *object)
{
	object->inv_transform = mult_n_mat4d(3, \
		&object->rot, &object->scale, &object->translate);
	object->inv_transform = inverse_mat4d(&object->inv_transform);
	printf("updated object type: %d\n", object->type);
}

static inline void	_move_sideways_check(t_minirt *minirt, bool *state_changed)
{
	t_object	*selected_object;
	t_vec4d		scaled_left;

	scale_vector(&scaled_left, &minirt->cam.left, \
		(MOVE_SPEED + (MOVE_SPEED / 2.f)) * minirt->delta_time);
	selected_object = minirt->selected.object;
	if (minirt->move.a || minirt->move.left)
	{
		selected_object->translate.matrix[3] += scaled_left.x;
		selected_object->translate.matrix[7] += scaled_left.y;
		selected_object->translate.matrix[11] += scaled_left.z;
		*state_changed = true;
	}
	if (minirt->move.d || minirt->move.right)
	{
		selected_object->translate.matrix[3] -= scaled_left.x;
		selected_object->translate.matrix[7] -= scaled_left.y;
		selected_object->translate.matrix[11] -= scaled_left.z;
		*state_changed = true;
	}
}

static inline void	_move_longitudinally_check(t_minirt *minirt, \
	bool *state_changed)
{
	t_object	*selected_object;
	t_vec4d		viewport_forward;
	t_point		op;

	selected_object = minirt->selected.object;
	op = create_point(selected_object->translate.matrix[3], \
		minirt->cam.from.y, selected_object->translate.matrix[11]);
	viewport_forward = subtract_points(&op, &minirt->cam.from);
	viewport_forward = normalize(&viewport_forward);
	scale_vector(&viewport_forward, &viewport_forward, \
		(MOVE_SPEED + (MOVE_SPEED / 2.f)) * minirt->delta_time);
	if (minirt->move.w)
	{
		selected_object->translate.matrix[3] += viewport_forward.x;
		selected_object->translate.matrix[7] += viewport_forward.y;
		selected_object->translate.matrix[11] += viewport_forward.z;
		*state_changed = true;
	}
	if (minirt->move.s)
	{
		selected_object->translate.matrix[3] -= viewport_forward.x;
		selected_object->translate.matrix[7] -= viewport_forward.y;
		selected_object->translate.matrix[11] -= viewport_forward.z;
		*state_changed = true;
	}
}

static inline void	_move_elevation_check(t_minirt *minirt, bool *state_changed)
{
	t_object	*selected_object;

	selected_object = minirt->selected.object;
	if (minirt->move.space || minirt->move.up)
	{
		selected_object->translate.matrix[7] += (MOVE_SPEED * \
			minirt->delta_time);
		*state_changed = true;
	}
	if (minirt->move.leftshift || minirt->move.down)
	{
		selected_object->translate.matrix[7] -= (MOVE_SPEED * \
			minirt->delta_time);
		*state_changed = true;
	}
}

void	object_controls(t_minirt *minirt)
{
	t_object	*selected_object;
	bool		state_changed;

	state_changed = false;
	selected_object = minirt->selected.object;
	_move_sideways_check(minirt, &state_changed);
	_move_longitudinally_check(minirt, &state_changed);
	_move_elevation_check(minirt, &state_changed);
	if (state_changed)
		update_object_cache(selected_object);
	minirt->changed = state_changed;
}
