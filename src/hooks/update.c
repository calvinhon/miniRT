/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:22:10 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 17:34:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>

static inline float get_delta_time(struct timespec *prev,
								   struct timespec *curr)
{
	return ((curr->tv_sec - prev->tv_sec) +
			(curr->tv_nsec - prev->tv_nsec) / 1e9f);
}

int update_rt(t_minirt *minirt)
{
	static struct timespec last_time;
	struct timespec curr_time;

	clock_gettime(CLOCK_MONOTONIC, &curr_time);
	if (last_time.tv_sec != 0 || last_time.tv_nsec != 0)
		minirt->delta_time = get_delta_time(&last_time, &curr_time);
	last_time = curr_time;
	if (!thread_arbiter(minirt))
		return (1);
	return (0);
}

static void update_stop(t_minirt *minirt)
{
	if (minirt->stop)
	{
		if (!minirt->selected.is_cam)
		{
			minirt->selected.is_cam = true;
			minirt->selected.object = NULL;
			minirt->stop = false;
			ft_printf("Camera is selected!\n");
		}
		else
			return (destroy_minirt(minirt), (void)0);
	}
}

static void update_state(t_minirt *minirt)
{
	update_stop(minirt);
	if (minirt->move.a || minirt->move.d || minirt->move.s || minirt->move.w || minirt->move.space || minirt->move.leftshift || minirt->move.up || minirt->move.down || minirt->move.left || minirt->move.right)
	{
		if (minirt->selected.is_cam)
		{
			camera_controls(minirt);
			camera_rotations(minirt);
			ft_printf("Camera is selected!\n");
		}
		else
		{
			object_controls(minirt);
			ft_printf("Object is selected!\n");
		}
	}
}

int update_minirt(t_minirt *minirt)
{
	update_state(minirt);
	if (minirt->changed || minirt->start)
	{
		ft_printf("Redrawing RT\n");
		update_rt(minirt);
		minirt->changed = false;
		minirt->start = false;
		ft_printf("Updated RT!\n");
	}
	return (0);
}
