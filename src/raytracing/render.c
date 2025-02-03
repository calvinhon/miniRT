/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:50:33 by chon              #+#    #+#             */
/*   Updated: 2025/01/20 16:50:33 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "colors.h"

t_itx *get_hit(t_itx_grp *xs)
{
	int i;
	t_itx *itx;
	float t0;

	i = -1;
	itx = NULL;
	t0 = FLT_MAX;
	while (++i < xs->count)
	{
		if (xs->arr[i].t < t0 && xs->arr[i].t > EPSILON)
		{
			itx = &xs->arr[i];
			t0 = xs->arr[i].t;
		}
	}
	return (itx);
}

t_comps prepare_computations(t_itx *itx, t_ray *r, t_itx_grp *xs)
{
	float bump;
	t_comps comps;
	t_vec4d	margin;

	comps.t = itx->t;
	comps.obj = itx->obj;
	comps.p = position(r, comps.t);
	comps.eye_v = negate_vector(&r->direction);
	normal_at(itx, &comps);
	bump = EPSILON * 10;
	scale_vector(&margin, &comps.normal_v, bump);
	comps.over_point = add_v_to_p(&comps.p, &margin);
	// lag_vec4s_scaleby(&margin, comps.normal_v, bump);
	// lag_vec4s_sub(&comps.under_point, &comps.p, &margin);
	comps.reflect_v = reflect(&r->direction, &comps.normal_v);
	if (comps.obj->material.refractive > 0.f)
		prepare_refractions(itx, &comps, xs);
	return (comps);
}

t_color color_at(t_scene *s, t_ray *r, int remaining)
{
	t_itx_grp	xs;
	t_itx		*hit;
	t_comps		comps;

	xs = intersect(s, r);
	hit = get_hit(&xs);
	if (!hit)
		return (create_color(0, 0, 0));
	comps = prepare_computations(hit, r, &xs);
	if (!remaining)
		return (create_color(0, 0, 0));
	return (shade_hit(s, &comps, remaining));
}

t_ray	cam_ray_to_pixel(const t_camera *cam, int px, int py)
{
	t_point	pixel_cam;
	t_point	pixel_world;
	t_point	cam_origin_world;
	t_vec4d	ray_direction;
	t_point	origin;

	pixel_cam = create_point((cam->half_width - (px + 0.5f) * cam->pixel_size),
				(cam->half_height - (py + 0.5f) * cam->pixel_size), -1);
	pixel_world = mult_mat4d_pt4d(&cam->inv_transform, &pixel_cam);
	origin = create_point(0, 0, 0);
	cam_origin_world = mult_mat4d_pt4d(&cam->inv_transform, &origin);
	ray_direction = subtract_points(&pixel_world, &cam_origin_world);
	ray_direction = normalize(&ray_direction);
	return (create_ray(&cam_origin_world, &ray_direction));
}

t_color	render_pixel(t_minirt *program, int x, int y)
{
	t_ray	r;
	t_color	c;

	r = cam_ray_to_pixel(&program->cam, x, y);
	c = color_at(&program->scene, &r, MAX_RFLX);
	put_pixel(&program->frame, x, y, &c);
	return (c);
}
