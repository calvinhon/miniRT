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

#include "miniRT.h"
#include <time.h>

static inline float	get_delta_time(struct timespec *prev,
						struct timespec *curr)
{
	return ((curr->tv_sec - prev->tv_sec) + \
		(curr->tv_nsec - prev->tv_nsec) / 1e9f);
}

int	update_rt(t_minirt *minirt)
{
	static struct timespec	last_time;
	struct timespec			curr_time;

	clock_gettime(CLOCK_MONOTONIC, &curr_time);
	if (last_time.tv_sec != 0 || last_time.tv_nsec != 0)
		minirt->delta_time = get_delta_time(&last_time, &curr_time);
	last_time = curr_time;
	if (!thread_arbiter(minirt))
		return (1);
	return (0);
}
