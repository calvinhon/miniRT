/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_minirt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:07:31 by marvin            #+#    #+#             */
/*   Updated: 2025/01/07 16:07:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	update_press(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_ESC)
		return (minirt->stop = 0, 0);
	if (keycode == KEY_R)
		minirt->scene.refract_reflect ^= false;
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
		minirt->move.lshift = false;
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
int	update_release(int keycode, t_minirt *minirt)
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
		minirt->move.lshift = false;
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


