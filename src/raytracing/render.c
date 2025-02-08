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

t_itx	*get_hit(t_itx_grp *xs)
{
	int		i;
	t_itx	*itx;
	float	t0;

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

void	local_normal_at(t_itx *itx, t_comps *comps)
{
	if (itx->obj->type == SPHERE)
		comps->normal_v = sphere_normal_at(itx->obj, &comps->p);
	else if (itx->obj->type == PLANE)
		comps->normal_v = plane_normal_at(itx->obj, &comps->p);
	else if (itx->obj->type == CYLINDER)
		comps->normal_v = cylinder_normal_at(itx->obj, &comps->p);
	else if (itx->obj->type == CUBE)
		comps->normal_v = cube_normal_at(itx->obj, &comps->p);
	else if (itx->obj->type == CONE)
		comps->normal_v = cone_normal_at(itx->obj, &comps->p);
	if (dot_pointers(&comps->normal_v, &comps->eye_v) < EPSILON)
		comps->normal_v = negate_vector(&comps->normal_v);
}

t_comps	prepare_computations(t_itx *itx, t_ray *r, t_itx_grp *xs)
{
	float	bump;
	t_comps	comps;
	t_vec4d	margin;

	comps.t = itx->t;
	comps.obj = itx->obj;
	comps.p = position(r, comps.t);
	comps.eye_v = negate_vector(&r->direction);
	local_normal_at(itx, &comps);
	bump = EPSILON * 10;
	scale_vector(&margin, &comps.normal_v, bump);
	comps.over_point = add_v_to_p(&comps.p, &margin);
	comps.reflect_v = reflect(&r->direction, &comps.normal_v);
	if (itx->obj->material.refractive > 0.f)
	{
		comps.under_point = subtract_v_from_p(&comps.p, &margin);
		prepare_refractions(xs, &itx);
		comps.n1 = itx->n1;
		comps.n2 = itx->n2;
	}
	return (comps);
}

t_color	color_at(t_scene *s, t_ray *r, int remaining)
{
	t_itx_grp	xs;
	t_itx		*hit;
	t_comps		comps;

	xs = local_intersect(s, r);
	hit = get_hit(&xs);
	if (!hit)
		return (create_color(0, 0, 0));
	comps = prepare_computations(hit, r, &xs);
	if (!remaining)
		return (create_color(0, 0, 0));
	return (shade_hit(s, &comps, remaining));
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
