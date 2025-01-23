/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:35:58 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 17:31:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	select_shape(int button, int x, int y, void *minirt)
{
	const t_camera	*cam = &((t_minirt *)minirt)->cam;
	t_scene			*w;
	t_ray			r;
	t_itx_grp		xs;
	t_itx			*hit;

	w = &((t_minirt *)minirt)->scene;
	if (button == MOUSE_LMB)
	{
		r = ray_for_pixel(cam, x, y);
		xs = intersect_world(w, &r);
		hit = get_hit(&xs);
		if (hit)
		{
			((t_minirt *)minirt)->selected.is_cam = false;
			((t_minirt *)minirt)->selected.object = hit->object;
		}
	}
	return (button);
}
