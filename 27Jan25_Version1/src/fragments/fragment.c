/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 07:07:39 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 17:34:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "colors.h"
#include "macros.h"

t_ray	ray_for_pixel(const t_camera *cam, int px, int py)
{
	t_ray	r;
	t_vec4s	op;
	t_vec4s	pixel;
	t_vec4s	origin;
	t_vec4s	direction;

	vec4sp_ini(&op, (cam->half_width - (px + 0.5f) * cam->pixel_size),
		(cam->half_height - (py + 0.5f) * cam->pixel_size), -1);
	cross_mat4s_vec4s(&cam->inv_transform, &op, &pixel);
	vec4sp_ini(&op, 0.f, 0.f, 0.f);
	cross_mat4s_vec4s(&cam->inv_transform, &op, &origin);
	sub_vec4s(&direction, &pixel, &origin);
	normalize_vec4s(&direction);
	ray_create(&r, &origin, &direction);
	return (r);
}

static void	prepare_comps_normal(t_itx *itx, t_itx_data *comps)
{
	if (itx->object->type == SPHERE)
		comps->normalv = sphere_normal_at(itx->object, &comps->p);
	else if (itx->object->type == PLANE)
		comps->normalv = plane_normal_at(itx->object, &comps->p);
	else if (itx->object->type == CYLINDER)
		comps->normalv = cylinder_normal_at(itx->object, &comps->p);
	else if (itx->object->type == CUBIC)
		comps->normalv = cube_normal_at(itx->object, &comps->p);
	else if (itx->object->type == CONE)
		comps->normalv = cone_normal_at(itx->object, &comps->p);
	if (dot_vec4s_re(&comps->normalv, &comps->eyev) < EPSILON)
	{
		comps->inside = true;
		negate_vec4s(&comps->normalv);
	}
	else
		comps->inside = false;
}

t_itx_data	prepare_computations(t_itx *itx, t_ray *r, t_itx_grp *itxs)
{
	const float	time = itx->t;
	const float	bump = EPSILON + (time / (time * time));
	t_itx_data	comps;
	t_vec4s		margin;

	comps.t = itx->t;
	comps.obj = itx->object;
	ray_position(&comps.p, r, comps.t);
	comps.eyev = r->direction;
	negate_vec4s_new(&comps.eyev, r->direction);
	prepare_comps_normal(itx, &comps);
	scale_vec4s(&margin, comps.normalv, bump);
	add_vec4s(&comps.over_point, &comps.p, &margin);
	sub_vec4s(&comps.under_point, &comps.p, &margin);
	comps.reflectv = reflect(&r->direction, &comps.normalv);
	if (comps.obj->material.refractive_index > 0.f)
		prepare_refractions(itx, &comps, itxs);
	return (comps);
}

t_color	color_at(t_scene *w, t_ray *r, int depth)
{
	t_itx_grp		world_itxs;
	t_itx			*hit;
	t_color			result;
	t_itx_data		comps;

	world_itxs = intersect_world(w, r);
	hit = get_hit(&world_itxs);
	if (!hit)
	{
		ini_color(&result, 0.f, 0.f, 0.f);
		return (result);
	}
	comps = prepare_computations(hit, r, &world_itxs);
	return (shade_hit(w, &comps, depth));
}

t_color	rt_render_pixel(t_minirt *minirt, int x, int y)
{
	t_ray		r;
	t_color		c;

	r = ray_for_pixel(&minirt->cam, x, y);
	c = color_at(&minirt->scene, &r, _RT_REFLECTION_DEPTH);
	put_pixel(&minirt->frame, x, y, &c);
	return (c);
}
