/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:47:50 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 17:34:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "mlx.h"
#include <stdio.h>
#include <sys/time.h>

extern void	*render_chunk(void *minirt);

long long	my_gettime(void)
{
	struct timeval	timeofday;

	if (gettimeofday(&timeofday, NULL) == -1)
		return ((void)write(2, "Error.\n", 8), -1);
	return ((timeofday.tv_sec * 1000) + (timeofday.tv_usec / 1000));
}

bool	ini_core(t_minirt *minirt)
{
	t_core	*thread;
	int			i;

	minirt->cores = malloc(sizeof(t_core) * _RT_NUM_THREADS);
	if (!minirt->cores)
		return (false);
	i = -1;
	while (++i < _RT_NUM_THREADS)
	{
		thread = &minirt->cores[i];
		thread->minirt = minirt;
		thread->id = i;
		thread->y = i * (minirt->cam.vsize / _RT_NUM_THREADS);
		thread->yend = (i + 1) * (minirt->cam.vsize / _RT_NUM_THREADS);
		pthread_mutex_init(&thread->mutex, NULL);
		pthread_cond_init(&thread->cond, NULL);
		thread->work_ready = false;
		pthread_create(&thread->thread, NULL, await_task, thread);
	}
	return (true);
}

void	pool_start_frame(t_minirt *minirt)
{
	t_core	*thread;
	int			i;

	i = -1;
	while (++i < _RT_NUM_THREADS)
	{
		thread = &minirt->cores[i];
		pthread_mutex_lock(&thread->mutex);
		thread->work_ready = true;
		pthread_cond_signal(&thread->cond);
		pthread_mutex_unlock(&thread->mutex);
	}
}

void	pool_wait_for_frame(t_minirt *minirt)
{
	t_core	*thread;
	int			i;

	i = -1;
	while (++i < _RT_NUM_THREADS)
	{
		thread = &minirt->cores[i];
		pthread_mutex_lock(&thread->mutex);
		while (thread->work_ready)
		{
			pthread_mutex_unlock(&thread->mutex);
			pthread_mutex_lock(&thread->mutex);
		}
		pthread_mutex_unlock(&thread->mutex);
	}
}

bool	thread_arbiter(t_minirt *minirt)
{
	long long	start_time;
	long long	frame_time;

	start_time = my_gettime();
	pool_start_frame(minirt);
	pool_wait_for_frame(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->frame.ptr,
		0, 0);
	frame_time = my_gettime() - start_time;
	printf("Frame took: %lld\n", frame_time);
	return (true);
}
