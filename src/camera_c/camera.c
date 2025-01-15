/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:55:07 by chon              #+#    #+#             */
/*   Updated: 2024/12/11 15:55:07 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	set_camera(float fov)
{
	t_camera	c;

	c.hsize = WINDOW_W;
	c.vsize = WINDOW_H;
	c.fov = fov;
	c.half_view = tan(fov / 2);
	c.aspect_ratio = c.hsize / c.vsize;
	if (c.aspect_ratio >= 1)
	{
		c.half_width = c.half_view;
		c.half_height = c.half_view / c.aspect_ratio;
	}
	else
	{
		c.half_width = c.half_view * c.aspect_ratio;
		c.half_height = c.half_view;
	}
	c.pixel_size = c.half_width * 2 / c.hsize;
	return (c);
}

t_mat4d	view_transform(t_point from, t_point to, t_vec4d up)
{
	t_mat4d	view_mat;
	t_vec4d	forward;
	t_vec4d	up_n;
	t_vec4d	left;
	t_vec4d	true_up;

	view_mat = identity_mat();
	forward = normalize(subtract_points(to, from));
	up_n = normalize(up);
	left = cross(forward, up_n);
	true_up = cross(left, forward);
	view_mat.matrix[0] = left.x;
	view_mat.matrix[1] = left.y;
	view_mat.matrix[2] = left.z;
	view_mat.matrix[4] = true_up.x;
	view_mat.matrix[5] = true_up.y;
	view_mat.matrix[6] = true_up.z;
	view_mat.matrix[8] = -forward.x;
	view_mat.matrix[9] = -forward.y;
	view_mat.matrix[10] = -forward.z;
	view_mat = mult_n_mat4d(2, translation_mat(-from.x, -from.y, -from.z),
		view_mat);
	return (view_mat);
}
