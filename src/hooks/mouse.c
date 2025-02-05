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

#include "minirt.h"

int select_shape(int button, int x, int y, void *minirt)
{
	const t_camera *cam = &((t_minirt *)minirt)->cam;
	t_scene *s;
	t_ray r;
	t_itx_grp xs;
	t_itx *hit;

	s = &((t_minirt *)minirt)->scene;
	if (button == MOUSE_LMB)
	{
		r = cam_ray_to_pixel(cam, x, y);
		xs = intersect(s, &r);
		hit = get_hit(&xs);
		if (hit)
		{
			((t_minirt *)minirt)->selected.is_cam = false;
			((t_minirt *)minirt)->selected.object = hit->obj;
		}
	}
	return (button);
}
