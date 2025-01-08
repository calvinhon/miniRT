
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:47:33 by marvin            #+#    #+#             */
/*   Updated: 2024/12/11 17:47:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	handle_keypress(int key, t_minirt *minirt)
{
	if (key == KEY_LEFT || key == KEY_A)
		minirt->scene.camera.origin.x -= 10;
	else if (key == KEY_RIGHT || key == KEY_D)
		minirt->scene.camera.origin.x += 10;
	else if (key == KEY_UP || key == KEY_W)
		minirt->scene.camera.origin.y += 10;
	else if (key == KEY_DOWN || key == KEY_S)
		minirt->scene.camera.origin.y -= 10;
	else if (key == KEY_C)
		minirt->scene.camera.origin.z -= 10;
	else if (key == KEY_V)
		minirt->scene.camera.origin.z += 10;
	else if (key == KEY_I)
		minirt->scene.camera.orientation.x += 10;
	else if (key == KEY_K)
		minirt->scene.camera.orientation.x -= 10;
	else if (key == KEY_J)
		minirt->scene.camera.orientation.y += 10;
	else if (key == KEY_L)
		minirt->scene.camera.orientation.y -= 10;
	else if (key == KEY_U)
		minirt->scene.camera.orientation.z += 10;
	else if (key == KEY_O)
		minirt->scene.camera.orientation.z -= 10;
	else if (key == KEY_ESC || key == KEY_Q)
		close_window(minirt, "Window Closed\n");
	ray_trace(minirt);
	return (0);
}