

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

//minirt->n_threads = 4;
//minirt->threads = (t_threads *)malloc(sizeof(t_threads)*minirt->n_threads);
void free_threads(minirt->threads)
{
	int i = 0;
	while (i < minirt->n_threads)
	{
		if (minirt->threads[1].thread)
			free(minirt->threads[1].thread);
		i++;
	}
	free(minirt->threads);
}
void free_mlx(void *mlx)
{
	if (mlx)
	{
		// Assuming mlx_destroy_display and mlx_loop_end are available functions
		mlx_destroy_display(mlx);
		mlx_loop_end(mlx);
		free(mlx);
	}
}

void free_objs(t_obj *objs, size_t n_objs)
{
	size_t i;

	i = 0;
	while (i < n_objs)
	{
		if (objs[i].data)
			free(objs[i].data);
		i++;
	}
	free(objs);
}

void free_lights(t_light **lights, int count)
{
	int i;

	if (!lights)
		return ;
	i = 0;
	while (i < count)
	{
		if (lights[i])
			free(lights[i]);
		i++;
	}
	free(lights);
}
//minirt->graphic.mlx = mlx_init();
//minirt->graphic.win = mlx_new_window(minirt->graphic.mlx, WINDOW_W, WINDOW_L, "miniRT");
//minirt->graphic.img = mlx_new_image(minirt->graphic.mlx, WINDOW_W, WINDOW_L);
//minirt->graphic.addr = mlx_get_data_addr(minirt->graphic.img, &minirt->graphic.bpp, &minirt->graphic.l_len, &minirt->graphic.end);
//minirt->scene.light = (t_light *)malloc(minirt->scene.l * sizeof(t_light));
//minirt->scene.objs = (t_object *)malloc(minirt->scene.n_objs * sizeof(t_object));
//minirt->scene.objs[idx].data = malloc(sizeof(t_sphere));

void free_objs()


void	free_minirt(t_minirt *minirt)
{
	if (!minirt)
		return ;
	if (minirt->threads)
	{
		int i = 0;
		while (i < minirt->n_threads)
		{
			if (minirt->threads->thread[i])
				free(minirt->threads->thread[i]);
			i++;
		}
		free(minirt->threads->thread);
		free(minirt->threads);
	}
	if (minirt->graphic.win)
		mlx_destroy_window(minirt->graphic.mlx, minirt->graphic.win);
	if (minirt->graphic.img)
		mlx_destroy_image(minirt->graphic.mlx, minirt->graphic.img);
	free_mlx(minirt->graphic.mlx);
<<<<<<< HEAD
	//free_scene(minirt->scene);
	free_threads(minirt->threads);
	free_objs(minirt->scene.objs);
	free_lights(minirt->scene.light);
=======
	free_scene(minirt->scene);
	free_threads(minirt->comp_units);
>>>>>>> fac9762a1543c7c015675c63cef213e9d71331ec
	free(minirt);
	minirt = NULL;
}

int	close_window(t_minirt *minirt, char *s)
{
	if (*s == 'c')
		s = "Window Closed\n";
	ft_printf("%s", s);
	mlx_clear_window(minirt->graphic.mlx, minirt->graphic.win);
	mlx_destroy_window(minirt->graphic.mlx, minirt->graphic.win);
	free_minirt(minirt);
	exit(OK);
	return (OK);
}
