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

#include "minirt.h"

static void	record_r(t_minirt *minirt, int keycode)
{
	minirt->changed = true;
	if (keycode == KEY_F)
	{
		minirt->scene.refract ^= true;
		ft_printf("Toggle refract(ON/OFF):%d\n", minirt->scene.refract);
	}
	if (keycode == KEY_R)
	{
		minirt->scene.fr_fl ^= true;
		ft_printf("Toggle reflecting (ON/OFF):%d\n", minirt->scene.fr_fl);
	}
}

int	record_keypress(int keycode, t_minirt *minirt)
{
	if (keycode == KEY_R || keycode == KEY_F)
		return (record_r(minirt, keycode), keycode);
	if (keycode == KEY_ESC)
		return (minirt->stop = true, 0);
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
