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

#include "minirt.h"

// int	mouse(int key, int x, int y, t_mlx_vars *env)
// {
// 	(void)x;
// 	(void)y;
// 	if (key == 5)
// 		env->adj.zoom_factor *= 1.03;
// 	else if (key == 4)
// 		env->adj.zoom_factor *= 0.98;
// 	create_grid(env, env->map);
// 	return (0);
// }

// void	key_triggers(int key, t_mlx_vars *env)
// {
// 	if (key == 123)
// 		env->adj.x_offset -= 10;
// 	else if (key == 124)
// 		env->adj.x_offset += 10;
// 	else if (key == 126)
// 		env->adj.y_offset -= 10;
// 	else if (key == 125)
// 		env->adj.y_offset += 10;
// 	else if (key == 13)
// 		env->adj.rotate_x += .05;
// 	else if (key == 0)
// 		env->adj.rotate_z += .05;
// 	else if (key == 1)
// 		env->adj.rotate_x -= .05;
// 	else if (key == 2)
// 		env->adj.rotate_z -= .05;
// 	else if (key == 24)
// 		env->adj.height_factor *= 1.05;
// 	else if (key == 27)
// 		env->adj.height_factor *= .98;
// }

int	x_close(t_mlx_vars *env)
{
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	exit (0);
}

int	key(int key, t_mlx_vars *env)
{
	printf("key: %d\n", key);
	if (key == ESC)
		return (x_close(env));
	// else if ((key >= 123 && key <= 126) || (key >= 83 && key <= 87)
	// 	|| (key >= 0 && key <= 2) || (key == 13) || (key == 27) || (key == 24))
	// 	key_triggers(key, env);
	// else if (key == 49)
	// 	projection(env);
	else
		return (0);
}

void	set_controls(t_mlx_vars *env)
{
	mlx_key_hook(env->win, key, env);
	// mlx_hook(env->win, 4, 0, mouse, env);
	mlx_hook(env->win, 17, 0, x_close, env);
}