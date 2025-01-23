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
#include "libft.h"
#include "colors.h"

t_mat4s	rt_get_cam_inverse(const t_mat4s *view)
{
	t_mat4s	ret;

	ret.a[0][0] = view->a[0][0];
	ret.a[0][1] = view->a[1][0];
	ret.a[0][2] = view->a[2][0];
	ret.a[1][0] = view->a[0][1];
	ret.a[1][1] = view->a[1][1];
	ret.a[1][2] = view->a[2][1];
	ret.a[2][0] = view->a[0][2];
	ret.a[2][1] = view->a[1][2];
	ret.a[2][2] = view->a[2][2];
	ret.a[0][3] = -(view->a[0][0] * view->a[0][3] + view->a[1][0]
			* view->a[1][3] + view->a[2][0] * view->a[2][3]);
	ret.a[1][3] = -(view->a[0][1] * view->a[0][3] + view->a[1][1]
			* view->a[1][3] + view->a[2][1] * view->a[2][3]);
	ret.a[2][3] = -(view->a[0][2] * view->a[0][3] + view->a[1][2]
			* view->a[1][3] + view->a[2][2] * view->a[2][3]);
	ret.a[3][0] = 0.0f;
	ret.a[3][1] = 0.0f;
	ret.a[3][2] = 0.0f;
	ret.a[3][3] = 1.0f;
	return (ret);
}

void	set_camera_orient(t_camera *cam)
{
	if (fabsf(cam->forward.x) < EPSILON && fabsf(cam->forward.z) < EPSILON)
		cam->left = vec4s_re(-1.0f, 0.0f, 0.0f, 0.0f);
	else
		cam->left = cross_vec4s_re(cam->forward,
				vec4s_re(0.0f, 1.0f, 0.0f, 0.0f));
	cam->left = normalize_vec4s_highp(cam->left);
	cam->up = cross_vec4s_re(cam->left, cam->forward);
	cam->up = normalize_vec4s_highp(cam->up);
	cam->inv_transform = inirows_mat4s_re(
			vec4s_re(cam->left.x, cam->left.y, cam->left.z, 0.0f),
			vec4s_re(cam->up.x, cam->up.y, cam->up.z, 0.0f),
			vec4s_re(-cam->forward.x, -cam->forward.y,
				-cam->forward.z, 0.0f),
			vec4s_re(0.0f, 0.0f, 0.0f, 1.0f)
			);
	cross_mat4s_mat4s(cam->inv_transform, translation_mat4s(
			-cam->trans.x, -cam->trans.y, -cam->trans.z),
		&cam->inv_transform);
	cam->inv_transform = rt_get_cam_inverse(&cam->inv_transform);
}

void	set_camera_fields(t_camera *cam)
{
	cam->is_set = true;
	cam->scale = vec4sp_re(1.f, 1.f, 1.f);
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

t_vec4s	parse_point(char *data, size_t *i)
{
	t_vec4s	point;

	point.x = parse_float(data, i);
	point.y = parse_float(data, i);
	point.z = parse_float(data, i);
	point.w = 1.0;

	return (point);
}

t_vec4s	parse_vector(char *data, size_t *i)
{
	t_vec4s	vector;

	vector.x = parse_float(data, i);
	vector.y = parse_float(data, i);
	vector.z = parse_float(data, i);
	vector.w = 0.0;

	return (vector);
}

void	parse_camera(t_minirt *minirt, char *data, size_t *i)
{
	(*i) += 1;
	minirt->cam.trans = parse_point(data, i);
	minirt->cam.forward = parse_vector(data, i);
	//
	is_normalised(&minirt->cam.forward, *i, minirt);
	//
	set_camera_orient(&minirt->cam);
	minirt->cam.fov = parse_float(data, i);
	if (minirt->cam.fov < -0.f || minirt->cam.fov > 180.f)
		return (free(data), errors(CER_CAM_FOV, ER_CAM_FOV, minirt));
	set_camera_fields(&minirt->cam);
}
