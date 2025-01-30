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

#include "miniRT.h"
#include "macros.h"
// #include "libft.h"
#include "colors.h"

void	set_camera_orient(t_camera *cam)
{
	t_mat4d view_mat;

	// printf("forward: %.2f %.2f %.2f\n", cam->forward.x, cam->forward.y, cam->forward.z);
	if (fabsf(cam->forward.x) < EPSILON && fabsf(cam->forward.z) < EPSILON)
		cam->left = create_vec4d(-1.0f, 0.0f, 0.0f);
	else
		cam->left = cross_values(cam->forward,
				create_vec4d(0.0f, 1.0f, 0.0f));
	// printf("left: %.2f %.2f %.2f\n", cam->left.x, cam->left.y, cam->left.z);
	view_mat = identity_mat();
	cam->up = cross_pointers(&cam->left, &cam->forward);
	// printf("up: %.2f %.2f %.2f\n", cam->up.x, cam->up.y, cam->up.z);
	view_mat.matrix[0] = cam->left.x;
	view_mat.matrix[1] = cam->left.y;
	view_mat.matrix[2] = cam->left.z;
	view_mat.matrix[4] = cam->up.x;
	view_mat.matrix[5] = cam->up.y;
	view_mat.matrix[6] = cam->up.z;
	view_mat.matrix[8] = -cam->forward.x;
	view_mat.matrix[9] = -cam->forward.y;
	view_mat.matrix[10] = -cam->forward.z;
	cam->inv_transform = mult_n_mat4d(2,
		translation_mat(-cam->from.x, -cam->from.y, -cam->from.z), view_mat);
	cam->inv_transform = inverse_mat4d(&cam->inv_transform);
}

void	set_camera_fields(t_camera *cam)
{
	cam->is_set = true;
	cam->scale = create_vec4d(1.f, 1.f, 1.f);
	cam->hsize = FRAME_W;
	cam->vsize = FRAME_H;
	cam->aspect_ratio = (float)cam->hsize / (float)cam->vsize;
	cam->half_view = tanf((cam->fov / 2.f) * ((float)PI / 180.0f));
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

t_point	parse_point(char *data, size_t *i)
{
	t_point	point;

	point.x = parse_float(data, i);
	point.y = parse_float(data, i);
	point.z = parse_float(data, i);
	point.p = 1.0;

	return (point);
}

t_vec4d	parse_vector(char *data, size_t *i)
{
	t_vec4d	vector;

	vector.x = parse_float(data, i);
	vector.y = parse_float(data, i);
	vector.z = parse_float(data, i);
	vector.p = 0.0;

	return (vector);
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
