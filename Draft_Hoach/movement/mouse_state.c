/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:10:59 by marvin            #+#    #+#             */
/*   Updated: 2025/01/07 18:10:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void lag_vec4sp_init(t_vector *vec, float x, float y, float z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
    vec->w = 1.0f; // Assuming a homogeneous coordinate for 4D vectors
}
t_ray	ray_cam2pixel(const t_camera *cam, int px, int py)
{
	t_ray		r;
	t_vector	op;
	t_vector	pixel;
	t_vector	origin;
	t_vector	direction;

	// initialize in the camera space
	op = vec4d(x, y, z, -1);
	lag_vec4sp_init(&op, (cam->half_width - (px + 0.5f) * cam->pixel_size),
		(cam->half_height - (py + 0.5f) * cam->pixel_size), -1);
	// transform the pixel in the world space
	lag_mat4s_cross_vec4s(&cam->inv_transform, &op, &pixel);
	// origin of the ray
	lag_vec4sp_init(&op, 0.f, 0.f, 0.f);
	// transform the origin in the world space
	lag_mat4s_cross_vec4s(&cam->inv_transform, &op, &origin);
	// ray direction
	lag_vec4s_sub(&direction, &pixel, &origin);
	lag_vec4s_normalize(&direction);
	ray_create(&r, &origin, &direction);
	return (r);
}
int	select_object(int click, int x, int y, t_minirt *minirt)
{
	const t_camera	*cam = &minirt->scene.camera;
	t_scene			*scene;
	t_ray			r;
	t_itx_set		xs;
	t_itx			*hit;

	scene = &minirt->scene;
	// left button click
	if (click == MOUSE_LB)
	{
		// create a ray from camera to pixel
		r = ray_cam2pixel(cam, x, y);
		// determine a set of shapes that intersect with the ray
		xs = interx2world(w, &r);
		// find the nearest intersection
		hit = get_hit(&xs);
		if (hit)
		{
			minirt->is_cam = false;
			minirt->obj = hit->object;
		}
	}
	return (click);
}