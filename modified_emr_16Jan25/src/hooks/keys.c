/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:11:55 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 17:34:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	update_minirt(t_minirt *minirt)
{
	if (minirt->stop)
	{
		if (!minirt->selected.is_cam)
		{
			minirt->selected.is_cam = true;
			minirt->selected.object = NULL;
			minirt->stop = false;
		}
		else
			return (destroy_minirt(minirt), 0);
	}
	if (minirt->selected.is_cam)
	{
		camera_controls(minirt);
		if (minirt->move.left || minirt->move.right
			|| minirt->move.up || minirt->move.down)
			camera_rotations(minirt);
	}
	else if (minirt->move.a || minirt->move.d || minirt->move.s
		|| minirt->move.w || minirt->move.space || minirt->move.leftshift)
		object_controls(minirt);
	return (update_rt(minirt), 0);
}

int	record_keypress(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_ESC)
		return (minirt->stop = true, 0);
	if (keycode == KEY_R)
		minirt->scene.refract_reflect ^= true;
	if (keycode == KEY_A)
		minirt->move.a = true;
	if (keycode == KEY_D)
		minirt->move.d = true;
	if (keycode == KEY_S)
		minirt->move.s = true;
	if (keycode == KEY_W)
		minirt->move.w = true;
	if (keycode == KEY_SPACE)
		minirt->move.space = true;
	if (keycode == KEY_LSHIFT)
		minirt->move.leftshift = true;
	if (keycode == AKEY_U)
		minirt->move.up = true;
	if (keycode == AKEY_D)
		minirt->move.down = true;
	if (keycode == AKEY_L)
		minirt->move.left = true;
	if (keycode == AKEY_R)
		minirt->move.right = true;
	return (keycode);
}

int	record_keyrelease(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_A)
		minirt->move.a = false;
	if (keycode == KEY_D)
		minirt->move.d = false;
	if (keycode == KEY_S)
		minirt->move.s = false;
	if (keycode == KEY_W)
		minirt->move.w = false;
	if (keycode == KEY_SPACE)
		minirt->move.space = false;
	if (keycode == KEY_LSHIFT)
		minirt->move.leftshift = false;
	if (keycode == AKEY_U)
		minirt->move.up = false;
	if (keycode == AKEY_D)
		minirt->move.down = false;
	if (keycode == AKEY_L)
		minirt->move.left = false;
	if (keycode == AKEY_R)
		minirt->move.right = false;
	return (keycode);
}
