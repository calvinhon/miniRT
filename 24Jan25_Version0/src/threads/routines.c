/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:31:02 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 17:34:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

void	*render_chunk(void *arg)
{
	const t_core		*data = (t_core *)arg;
	t_camera			*cam;
	int					x;
	int					y;
	int					yend;

	y = data->y;
	yend = data->yend;
	cam = &data->minirt->cam;
	while (y < yend)
	{
		x = 0;
		while (x < cam->hsize)
		{
			rt_render_pixel(data->minirt, x, y);
			x += STEP_SKIP;
		}
		y += STEP_SKIP;
	}
	interpolate_horizontal(data);
	interpolate_vertical(data);
	return (NULL);
}

void	*await_task(void *arg)
{
	t_core	*data;

	data = (t_core *)arg;
	while (true)
	{
		pthread_mutex_lock(&data->mutex);
		while (!data->minirt->stop && !data->work_ready)
			pthread_cond_wait(&data->cond, &data->mutex);
		if (data->minirt->stop)
		{
			pthread_mutex_unlock(&data->mutex);
			break ;
		}
		pthread_mutex_unlock(&data->mutex);
		render_chunk(data);
		pthread_mutex_lock(&data->mutex);
		data->work_ready = false;
		pthread_mutex_unlock(&data->mutex);
	}
	return (NULL);
}
