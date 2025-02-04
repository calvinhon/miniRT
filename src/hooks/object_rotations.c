/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objera_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:38:22 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 17:31:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline void	_rotobj_apply_pitch_rot(t_minirt *minirt, bool left, \
	bool *state_changed)
{
	const float	angle = (PITCH_SPEED + MOVE_SPEED / 10.f) * minirt->delta_time;
	t_mat4d		rot;
	t_object	*selected_object;

	selected_object = minirt->selected.object;
	if (left)
		rot = rotate_mat_x(-angle);
	else
		rot = rotate_mat_x(angle);
	selected_object->rot = mult_n_mat4d(2, &rot, &selected_object->rot);
	//
	ft_printf("rotated object x\n");
	//selected_object->rot = rt_extract_rot_vertical(selected_object->orientation);
	*state_changed = true;
}

static inline void	_rotobj_apply_yaw_rot(t_minirt *minirt, \
	bool up, bool *state_changed)
{
	const float	angle = (YAW_SPEED + MOVE_SPEED / 10.f) * minirt->delta_time;
	t_mat4d		rot;
	t_object	*selected_object;

	selected_object = minirt->selected.object;
	if (up)
		rot = rotate_mat_z(angle);
	else
		rot = rotate_mat_z(-angle);
	selected_object->rot = mult_n_mat4d(2, &rot, &selected_object->rot);
		//
	ft_printf("rotated object yaw\n");
	*state_changed = true;
}

void	object_rotations(t_minirt *minirt)
{
	bool	state_changed;

	state_changed = false;
	if (minirt->move.left == true)
		_rotobj_apply_pitch_rot(minirt, true, &state_changed);
	if (minirt->move.right == true)
		_rotobj_apply_pitch_rot(minirt, false, &state_changed);
	if (minirt->move.up == true)
		_rotobj_apply_yaw_rot(minirt, true, &state_changed);
	if (minirt->move.down == true)
		_rotobj_apply_yaw_rot(minirt, false, &state_changed);
	if (state_changed)
		update_object_cache(minirt->selected.object);
	minirt->changed = minirt->changed || state_changed;
}
