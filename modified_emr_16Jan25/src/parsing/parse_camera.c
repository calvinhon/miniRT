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

void	get_camera_orient(t_camera *cam)
{
	is_normalised(&cam->forward, cam->line_set);
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

void	get_camera_extras(t_camera *cam, int curr_line)
{
	cam->is_set = true;
	cam->line_set = curr_line;
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

bool	parse_camera(t_minirt *minirt, const t_split *fields, int curr_line)
{
	t_camera	*camera;
	float		temp;

	camera = &minirt->cam;
	if (camera->is_set)
		return (parse_fatal_msg(ER_CAM_DEFINED, curr_line),
			destroy_2d_arr(fields->array), false);
	if (fields->wordcount != 4)
		return (parse_err_msg(ER_CAM_FORMAT, ER_EXPECT_TYPE_C, curr_line),
			destroy_2d_arr(fields->array), false);
	if (!parse_vec4p(&camera->trans, fields->array[1], minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	if (!parse_vec4v(&camera->forward, fields->array[2], minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	get_camera_orient(camera);
	temp = ft_atof(fields->array[3], minirt);
	if (temp < -0.f || temp > 180.f)
		return (parse_err_msg(ER_CAM_FOV, ER_E_FOV_RANGE, curr_line),
			destroy_2d_arr(fields->array), false);
	else if (temp == 0.f || temp == -0.f)
		parse_warn_msg("Viewport will be an infinitely small line", NULL,
			curr_line, false);
	camera->fov = temp;
	get_camera_extras(camera, curr_line);
	return (destroy_2d_arr(fields->array), true);
}
