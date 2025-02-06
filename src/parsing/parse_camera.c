/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:11:06 by nth          #+#    #+#             */
/*   Updated: 2024/10/16 16:33:24 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "macros.h"
#include "colors.h"

t_mat4d	rt_get_cam_inverse(const t_mat4d *view)
{
	t_mat4d	ret;
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			ret.matrix[i * 4 + j] = view->matrix[j * 4 + i];
			j++;
		}
		ret.matrix[i * 4 + 3] = -(view->matrix[0 * 4 + i] * view->matrix[0 * 4 + 3] +
								  view->matrix[1 * 4 + i] * view->matrix[1 * 4 + 3] +
								  view->matrix[2 * 4 + i] * view->matrix[2 * 4 + 3]);
		i++;
	}
	ret.matrix[12] = 0.0f;
	ret.matrix[13] = 0.0f;
	ret.matrix[14] = 0.0f;
	ret.matrix[15] = 1.0f;
	return (ret);
}

void	set_camera_orient(t_camera *cam)
{
	t_mat4d	view_m;
	t_mat4d	translate_m;

	if (fabsf(cam->forward.x) < EPSILON && fabsf(cam->forward.z) < EPSILON)
		cam->left = create_vec4d(-1.0f, 0.0f, 0.0f);
	else
		cam->left = cross_values(cam->forward, \
			create_vec4d(0.0f, 1.0f, 0.0f));
	cam->left = normalize(&cam->left);
	cam->up = cross_values(cam->left, cam->forward);
	cam->up = normalize(&cam->up);
	view_m = identity_mat();
	view_m.matrix[0] = cam->left.x;
	view_m.matrix[1] = cam->left.y;
	view_m.matrix[2] = cam->left.z;
	view_m.matrix[4] = cam->up.x;
	view_m.matrix[5] = cam->up.y;
	view_m.matrix[6] = cam->up.z;
	view_m.matrix[8] = -cam->forward.x;
	view_m.matrix[9] = -cam->forward.y;
	view_m.matrix[10] = -cam->forward.z;
	translate_m = translation_mat(-cam->from.x, -cam->from.y, -cam->from.z);
	cam->inv_transform = mult_n_mat4d(2, &translate_m, &view_m);
	cam->inv_transform = inverse_mat4d(&cam->inv_transform);
}

void	set_camera_fields(t_camera *cam)
{
	cam->is_set = true;
	cam->scale = create_vec4d(1.f, 1.f, 1.f);
	cam->hsize = FRAME_W;
	cam->vsize = FRAME_H;
	cam->aspect_ratio = (float)cam->hsize / (float)cam->vsize;
	cam->half_view = tanf((cam->fov / 2.f) * ((float)M_PI / 180.0f));
	if (cam->aspect_ratio >= 1.0f)
	{
		cam->half_width = cam->half_view;
		cam->half_height = cam->half_view / cam->aspect_ratio;
	}
	else
	{
		cam->half_width = cam->half_view * cam->aspect_ratio;
		cam->half_height = cam->half_view;
	}
	cam->pixel_size = (cam->half_width * 2.f) / cam->hsize;
}

void	parse_camera(t_minirt *minirt, char *data, size_t *i)
{
	(*i) += 1;
	minirt->cam.from = parse_point(data, i);
	minirt->cam.forward = parse_vector(data, i);
	is_normalised(&minirt->cam.forward, *i, minirt);
	set_camera_orient(&minirt->cam);
	minirt->cam.fov = parse_float(data, i);
	if (minirt->cam.fov < -0.f || minirt->cam.fov > 180.f)
		return (free(data), errors(CER_CAM_FOV, ER_CAM_FOV, minirt));
	set_camera_fields(&minirt->cam);
}
