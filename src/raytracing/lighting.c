/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:00:44 by chon              #+#    #+#             */
/*   Updated: 2025/01/22 11:00:44 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "colors.h"

t_color	lighting(t_material *m, t_light *l, t_comps *c, t_color *ambiance)
{
	t_color	effective_color;
	t_vec4d	light_v;
	float	light_dot_normal;
	float	refl_d_eye;

	if (m->pattern)
		m->color = pattern_at(c->obj, &c->p, m->pattern);
	c->diffuse = create_color(0, 0, 0);
	c->specular = create_color(0, 0, 0);
	effective_color = mult_colors(&m->color, &l->intensity);
	c->ambient = mult_colors(&effective_color, ambiance);
	light_v = subtract_points(&l->pos, &c->p);
	light_v = normalize(&light_v);
	light_dot_normal = dot_pointers(&light_v, &c->normal_v);
	if (light_dot_normal >= 0 && !c->shadowed)
	{
		c->diffuse = scale_color(&effective_color, m->diffuse_s);
		c->diffuse = scale_color(&c->diffuse, light_dot_normal);
		light_v = negate_vector(&light_v);
		refl_d_eye = dot_values(reflect(&light_v, &c->normal_v), c->eye_v);
		if (refl_d_eye > 0)
			c->specular = scale_color(&l->intensity, pow(refl_d_eye, \
				m->shininess) * m->specular_s);
	}
	return (add_colors(3, &c->ambient, &c->diffuse, &c->specular));
}

bool	is_shadowed(t_scene *s, t_point *p, t_light *l)
{
	t_vec4d		light_v;
	t_vec4d		normalized_v;
	t_ray		r;
	t_itx_grp	xs;
	t_itx		*h;

	light_v = subtract_points(p, &l->pos);
	normalized_v = normalize(&light_v);
	if (l->type == SPOT_LIGHT
		&& dot_pointers(&l->orientation, &normalized_v) < l->spot_angle)
		return (true);
	light_v = subtract_points(&l->pos, p);
	normalized_v = normalize(&light_v);
	r = create_ray(p, &normalized_v);
	xs = local_intersect(s, &r);
	h = get_hit(&xs);
	if (h && h->t < magnitude(&light_v))
		return (true);
	return (false);
}

t_color	reflected_color(t_scene *s, t_comps *c, int remaining)
{
	t_ray	reflect_r;
	t_color	color;

	reflect_r = create_ray(&c->over_point, &c->reflect_v);
	color = color_at(s, &reflect_r, remaining - 1);
	return (scale_color(&color, c->obj->material.reflective));
}

static void	compute_lighting(t_scene *s, t_comps *c, t_shade_hit *color)
{
	int	i;

	i = -1;
	while (++i < s->num_lights)
	{
		c->shadowed = is_shadowed(s, &c->over_point, &s->lights[i]);
		if (i == 0)
			color->local_ambiance = s->ambiance;
		else
			color->local_ambiance = create_color(0, 0, 0);
		color->lighting_result = lighting(&c->obj->material, \
			&s->lights[i], c, &color->local_ambiance);
		color->surface = add_colors(2, &color->surface, \
			&color->lighting_result);
	}
}

t_color	shade_hit(t_scene *s, t_comps *c, int remaining)
{
	t_shade_hit	color;

	color.surface = create_color(0, 0, 0);
	color.reflect = color.surface;
	color.refract = color.surface;
	compute_lighting(s, c, &color);
	if (s->refract && c->obj->material.transparency)
		color.surface = scale_color(&color.surface, \
			1 - c->obj->material.transparency);
	if (s->fr_fl && c->obj->material.reflective)
		color.reflect = reflected_color(s, c, remaining);
	if (s->refract && c->obj->material.refractive)
		color.refract = refracted_color(s, c, remaining);
	return (add_colors(3, &color.surface, &color.reflect, &color.refract));
}
