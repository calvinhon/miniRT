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

t_camera	set_camera()
{
	t_camera	cam;

	cam.hsize = WINDOW_W;
	cam.vsize = WINDOW_H;
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
