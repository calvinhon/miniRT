/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:38:41 by marvin            #+#    #+#             */
/*   Updated: 2025/01/08 16:38:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	move_render(t_minirt *minirt)
{
	if (minirt->stop)
	{
		if (!minirt->is_cam)
		{
			minirt->is_cam = true;
			minirt->obj = NULL;
			minirt->stop = false;
		}
		else
			return (close_minirt(minirt), 0);
	}
	if (minirt->is_cam)
	{
		camera_controls(minirt);
		if (minirt->move.left || minirt->move.right	|| minirt->move.up || minirt->move.down)
			camera_rotations(minirt);
	}
	else if (minirt->move.a || minirt->move.d || minirt->move.s
		|| minirt->move.w || minirt->move.space || minirt->move.lshift)
		object_controls(minirt);
	return (render(minirt), 0);
}
