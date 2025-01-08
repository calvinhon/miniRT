/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0errors_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:39:11 by honguyen          #+#    #+#             */
/*   Updated: 2025/01/07 18:10:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void free_scene(t_minirt *minirt)
{
	size_t i;

	i = 0;
	while (i < minirt->scene.n_objs)
	{
		if (minirt->scene.objs[i].data)
			free(minirt->scene.objs[i].data);
		i++;
	}
	free(minirt->scene.objs);
	minirt->scene.objs = NULL;
	if (minirt->scene.light)
		free(minirt->scene.light);
	minirt->scene.light = NULL;
}

void	free_textures(t_minirt *minirt)
{
	t_list	*temp;

	temp = minirt->textures;
	while (temp)
	{
		free(((t_texture *)temp->content)->name);
		mlx_destroy_image(minirt->mlx,
			((t_texture *)temp->content)->tex->img);
		free(((t_texture *)temp->content)->tex);
		temp = temp->next;
	}
	ft_lstclear(&minirt->textures, free);
}

void	free_mlx(t_minirt *minirt)
{
	if (minirt->mlx)
	{
		mlx_destroy_image(minirt->mlx, minirt->frame.img);
		mlx_destroy_window(minirt->mlx, minirt->win);
		mlx_loop_end(minirt->mlx);
		free(minirt->mlx);
	}
}

int	close_minirt(t_minirt *minirt)
{
	int	i;

	if (minirt->units)
	{
		minirt->stop = true;
		i = -1;
		while (++i < _RT_NUM_THREADS)
		{
			pthread_mutex_lock(&minirt->units[i].mutex);
			pthread_cond_signal(&minirt->units[i].cond);
			pthread_mutex_unlock(&minirt->units[i].mutex);
			pthread_mutex_destroy(&minirt->units[i].mutex);
			pthread_cond_destroy(&minirt->units[i].cond);
		}
		i = -1;
		while (++i < _RT_NUM_THREADS)
			pthread_join(minirt->units[i].thread, NULL);
		free(minirt->units);
		minirt->units = NULL;
	}
	free_scene(minirt);
	free_textures(minirt);
	free_mlx(minirt);
	free(minirt);
	return (minirt = NULL, exit(0), 0);
}

void	errors(int err_code, t_minirt *minirt)
{
	if (minirt)
		close_minirt(minirt);
	ft_putstr_fd(MS_ER[err_code], 2);
	exit(err_code);
}
