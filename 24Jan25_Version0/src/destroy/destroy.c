/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 06:06:16 by nth          #+#    #+#             */
/*   Updated: 2024/10/07 09:26:22 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "miniRT.h"
#include "macros.h"

void	destroy_mlx(t_minirt *minirt)
{
	if (minirt->mlx)
	{
		mlx_destroy_image(minirt->mlx, minirt->frame.ptr);
		mlx_destroy_window(minirt->mlx, minirt->win);
		free(minirt->mlx);
		minirt->mlx = NULL;
	}
}

void	destroy_scene(t_minirt *minirt)
{
	if (minirt->scene.lights)
		free(minirt->scene.lights);
	if (minirt->scene.lights)	
		free(minirt->scene.shapes);
	minirt->scene.lights = NULL;
	minirt->scene.shapes = NULL;
}

void	destroy_textures(t_minirt *minirt)
{
	t_list	*temp;

	temp = minirt->textures;
	while (temp)
	{
		if (((t_tex_frame *)temp->content)->name)
			free(((t_tex_frame *)temp->content)->name);
		mlx_destroy_image(minirt->mlx,
			((t_tex_frame *)temp->content)->fra_tex->ptr);
		free(((t_tex_frame *)temp->content)->fra_tex);
		temp = temp->next;
	}
	ft_lstclear(&minirt->textures, free);
}

void	destroy_cores(t_minirt *minirt)
{
	int	i;

	if (minirt->cores)
	{
		minirt->stop = true;
		i = -1;
		while (++i < _RT_NUM_THREADS)
		{
			pthread_mutex_lock(&minirt->cores[i].mutex);
			pthread_cond_signal(&minirt->cores[i].cond);
			pthread_mutex_unlock(&minirt->cores[i].mutex);
			pthread_mutex_destroy(&minirt->cores[i].mutex);
			pthread_cond_destroy(&minirt->cores[i].cond);
		}
		i = -1;
		while (++i < _RT_NUM_THREADS)
			pthread_join(minirt->cores[i].thread, NULL);
		free(minirt->cores);
		minirt->cores = NULL;
	}
}

void	free_minirt(t_minirt *minirt)
{
	if (!minirt)
		return ;
	if (minirt->data)
		free(minirt->data);
	destroy_cores(minirt);
	destroy_scene(minirt);
	destroy_textures(minirt);
	destroy_mlx(minirt);
	free(minirt);
	minirt = NULL;
}

int	destroy_minirt(t_minirt *minirt)
{
	free_minirt(minirt);
	exit(0);
	return (0);
}

void	destroy_2d_arr(char **arr)
{
	char	**original;

	if (!arr)
		return ;
	original = arr;
	while (*arr)
		free(*arr++);
	free(original);
}
