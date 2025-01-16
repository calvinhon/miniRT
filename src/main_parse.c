/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_h.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:44:06 by chon              #+#    #+#             */
/*   Updated: 2024/12/19 01:21:02 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minirt.h"

void	ini_graphic(t_minirt *minirt)
{
    
	minirt->mlx = mlx_init();
	if (!minirt->mlx)
		errors(ER_MLX, minirt);
    minirt->win = mlx_new_window(minirt->mlx, WIDTH, HEIGHT, "MiniRT");
    minirt->frame.img = mlx_new_image(minirt->mlx, WIDTH, HEIGHT);
	if (!minirt->frame.img)
		errors(ER_MLX, minirt);
	minirt->frame.addr = mlx_get_data_addr(minirt->frame.img, &minirt->frame.bpp, &minirt->frame.l_len, 
		&minirt->frame.end);
	if (!minirt->frame.addr)
		errors(ER_MLX, minirt);
}

// void	ini_threads(t_minirt *minirt)
// {
// 	t_unit	*unit;
// 	int			i;

// 	minirt->units = malloc(sizeof(t_unit) * _RT_NUM_THREADS);
// 	if (!minirt->units)
// 		errors(ER_MALLOC, minirt);
// 	i = -1;
// 	while (++i < _RT_NUM_THREADS)
// 	{
// 		unit = &minirt->units[i];
// 		unit->minirt = minirt;
// 		unit->id = i;
// 		unit->y = i * (minirt->scene.camera.vsize / _RT_NUM_THREADS);
// 		unit->y_f = (i + 1) * (minirt->scene.camera.vsize / _RT_NUM_THREADS);
// 		pthread_mutex_init(&unit->mutex, NULL);
// 		pthread_cond_init(&unit->cond, NULL);
// 		unit->ready = false;
// 		pthread_create(&unit->thread, NULL, common_task, unit);
// 	}
// }

// void	*common_task(void *arg)
// {
// 	t_unit	*unit;

// 	unit = (t_unit *)arg;
// 	while (true)
// 	{
// 		pthread_mutex_lock(&unit->mutex);
// 		while (!unit->minirt->stop && !unit->ready)
// 			pthread_cond_wait(&unit->cond, &unit->mutex);
// 		if (unit->minirt->stop)
// 		{
// 			pthread_mutex_unlock(&unit->mutex);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&unit->mutex);
// 		render(unit);
// 		pthread_mutex_lock(&unit->mutex);
// 		unit->ready = false;
// 		pthread_mutex_unlock(&unit->mutex);
// 	}
// 	return (NULL);
// }

// void	*render(void *arg)
// {
// 	const t_unit		*unit = (t_unit *)arg;
// 	t_camera			*cam;
// 	int					x;
// 	int					y;
// 	int					y_f;

// 	y = unit->y;
// 	y_f = unit->y_f;
// 	cam = &unit->minirt->scene.camera;
// 	while (y < y_f)
// 	{
// 		x = 0;
// 		while (x < cam->hsize)
// 		{
// 			rt_render_pixel(unit->minirt, x, y);
// 			x += STEP;
// 		}
// 		y += STEP;
// 	}
// 	interpolate_horizontal(unit);
// 	interpolate_vertical(unit);
// 	return (NULL);
// }



int	main(int ac, char **av)
{
	t_minirt	*minirt;

	if (ac != 2)
		errors(ER_AGC, NULL);
	check_filename(av[1]);
	minirt = new_minirt();
	// parse including malloc for objects & lights
	parse(minirt, av[1]);
	// Intialize graphic mlx, window, image
	// ini_graphic(minirt);
	// // Initialize threads
	// ini_threads(minirt);
	// // Set intial controls for objs
	// minirt->is_cam = true;
	// minirt->obj = NULL;
	// // update_press(int keycode, t_minirt *minirt) set moving status
	// mlx_hook(minirt->win, KEY_PRESS, 1L, &update_press, minirt);
	// // update_release(int keycode, t_minirt *minirt) set moving status
	// mlx_hook(minirt->win, KEY_RELEASE, 1L << 1, &update_release, minirt);
	// // close_minirt(t_minirt *minirt) close minirt window
	// mlx_hook(minirt->win, KEY_DESTROY, 1L >> 2, &close_minirt, minirt);
	// // Detect the hit of mouse to an object to move it
	// mlx_mouse_hook(minirt->win, &select_object, minirt);
	// // move or change selected objects, raytracing and check for all threads done
	// mlx_loop_hook(minirt->mlx, &move_render, minirt);
	// mlx_loop(minirt->mlx);
	return (OK);
}

