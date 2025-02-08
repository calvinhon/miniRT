/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:50:33 by chon              #+#    #+#             */
/*   Updated: 2025/01/20 16:50:33 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	position(t_ray *r, float t)
{
	t_vec4d	scaled_v;

	scale_vector(&scaled_v, &r->direction, t);
	return (add_v_to_p(&r->origin, &scaled_v));
}

t_ray	create_ray(t_point *origin, t_vec4d *direction)
{
	t_ray	r;

	r.origin = *origin;
	r.direction = *direction;
	return (r);
}

void	transform_ray(t_ray *r, t_mat4d *m)
{
	r->origin = mult_mat4d_pt4d(m, &r->origin);
	r->direction = mult_mat4d_vec4d(m, &r->direction);
}

t_ray	cam_ray_to_pixel(const t_camera *cam, int px, int py)
{
	t_point	pixel_cam;
	t_point	pixel_world;
	t_point	cam_origin_world;
	t_vec4d	ray_direction;
	t_point	origin;

	pixel_cam = create_point((cam->half_width - (px + 0.5f) * cam->pixel_size), \
		(cam->half_height - (py + 0.5f) * cam->pixel_size), -1);
	pixel_world = mult_mat4d_pt4d(&cam->inv_transform, &pixel_cam);
	origin = create_point(0, 0, 0);
	cam_origin_world = mult_mat4d_pt4d(&cam->inv_transform, &origin);
	ray_direction = subtract_points(&pixel_world, &cam_origin_world);
	ray_direction = normalize(&ray_direction);
	return (create_ray(&cam_origin_world, &ray_direction));
}

t_vec4d	reflect(t_vec4d *in, t_vec4d *normal)
{
	float	in_dot_normal;
	t_vec4d	scaled_vec;

	in_dot_normal = dot_pointers(in, normal);
	scale_vector(&scaled_vec, normal, 2.f * in_dot_normal);
	return (subtract_vectors(in, &scaled_vec));
}
