/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:26:14 by chon              #+#    #+#             */
/*   Updated: 2024/12/11 15:47:27 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// int	mouse(int key, int x, int y, t_frame *frame)
// {
// 	(void)x;
// 	(void)y;
// 	if (key == 5)
// 		frame->adj.zoom_factor *= 1.03;
// 	else if (key == 4)
// 		frame->adj.zoom_factor *= 0.98;
// 	create_grid(frame, frame->map);
// 	return (0);
// }

// void	key_triggers(int key, t_frame *frame)
// {
// 	if (key == 123)
// 		frame->adj.x_offset -= 10;
// 	else if (key == 124)
// 		frame->adj.x_offset += 10;
// 	else if (key == 126)
// 		frame->adj.y_offset -= 10;
// 	else if (key == 125)
// 		frame->adj.y_offset += 10;
// 	else if (key == 13)
// 		frame->adj.rotate_x += .05;
// 	else if (key == 0)
// 		frame->adj.rotate_z += .05;
// 	else if (key == 1)
// 		frame->adj.rotate_x -= .05;
// 	else if (key == 2)
// 		frame->adj.rotate_z -= .05;
// 	else if (key == 24)
// 		frame->adj.height_factor *= 1.05;
// 	else if (key == 27)
// 		frame->adj.height_factor *= .98;
// }

int	x_close(t_frame *frame)
{
	mlx_destroy_image(frame->mlx, frame->img);
	mlx_destroy_window(frame->mlx, frame->win);
	exit (0);
}

int	key(int key, t_frame *frame)
{
	// printf("key: %d\n", key);
	if (key == KEY_ESC)
		return (x_close(frame));
	// else if ((key >= 123 && key <= 126) || (key >= 83 && key <= 87)
	// 	|| (key >= 0 && key <= 2) || (key == 13) || (key == 27) || (key == 24))
	// 	key_triggers(key, frame);
	// else if (key == 49)
	// 	projection(frame);
	else
		return (0);
}

void	set_controls(t_frame *frame)
{
	mlx_key_hook(frame->win, key, frame);
	// mlx_hook(frame->win, 4, 0, mouse, frame);
	// mlx_key_hook(frame->win, x_close, frame);
	mlx_hook(frame->win, 17, 0, x_close, frame);
}