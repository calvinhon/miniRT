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

#include "miniRT.h"
#include "colors.h"

t_vec4d reflect(t_vec4d *in, t_vec4d *normal)
{
	float in_dot_normal;
	t_vec4d scaled_vec;

	in_dot_normal = dot(*in, *normal);
	scaled_vec = scale_vector(*normal, 2.f * in_dot_normal);
	return (subtract_vectors(*in, scaled_vec));
}

t_color lighting(t_material *m, t_light *l, t_comps *c, t_color *ambiance)
{
	t_color effective_color;
	t_vec4d light_v;
	float light_dot_normal;
	float reflect_dot_eye;

	// if (m->pattern)
	// 	m->color = pattern_at(c->obj, &c->p, m->pattern);
	c->diffuse = create_color(0, 0, 0);
	c->specular = create_color(0, 0, 0);
	effective_color = mult_colors(m->color, c->l_color);
	c->ambient = mult_colors(effective_color, *ambiance);
	light_v = normalize(subtract_points(l->pos, c->p));
	light_dot_normal = dot(light_v, c->normal_v);
	if (light_dot_normal >= 0 && !c->shadowed)
	{
		c->diffuse = scale_color(effective_color, m->diffuse_s);
		c->diffuse = scale_color(c->diffuse, light_dot_normal);
		light_v = negate_vector(light_v);
		reflect_dot_eye = dot(reflect(&light_v, &c->normal_v), c->eye_v);
		if (reflect_dot_eye > 0)
		{
			c->specular = scale_color(c->l_color,
				pow(reflect_dot_eye, m->shininess) * m->specular_s);
		}
	}
	return (add_colors(3, c->ambient, c->diffuse, c->specular));
}

bool is_shadowed(t_scene *s, t_point *p, t_light *l)
{
	t_vec4d l_v;
	t_vec4d direction;
	t_ray r;
	t_itx_grp xs;
	t_itx *h;

	l_v = subtract_points(l->pos, *p);
	direction = normalize(l_v);
	r = create_ray(p, &direction);
	xs = local_intersect(s, &r);
	h = get_hit(&xs);
	if (h && h->t < magnitude(l_v))
		return (true);
	return (false);
}

t_color reflected_color(t_scene *s, t_comps *c, int remaining)
{
	t_ray reflect_r;
	t_color color;

	reflect_r = create_ray(&c->over_point, &c->reflect_v);
	color = color_at(s, &reflect_r, remaining - 1);
	return (scale_color(color, c->obj->material.reflective));
}

t_color shade_hit(t_scene *s, t_comps *c, int remaining)
{
	t_color lighting_result;
	t_color reflect;
	t_color surface;
	int i;

	surface = create_color(0, 0, 0);
	reflect = surface;
	i = -1;
	while (++i < s->num_lights)
	{
		if (s->lights[i].type == SPOT_LIGHT)
			c->l_color = s->lights[i].specs.spot.intensity;
		else
			c->l_color = s->lights[i].specs.point.intensity;
		c->shadowed = is_shadowed(s, &c->over_point, &s->lights[i]);
		if (i > 0)
			s->ambiance = create_color(0, 0, 0);
		lighting_result = lighting(&c->obj->material,
			&s->lights[i], c, &s->ambiance);
		surface = add_colors(2, surface, lighting_result);
	}
	if (c->obj->material.reflective)
		reflect = reflected_color(s, c, remaining);
	// if (s->refract_reflect)
	// {
	// 	refract_reflect = check_for_refref(s, comps, remaining);
	// 	color_add(&color, &color, &refract_reflect);
	// }
	// color_add(&color, &color, &s->ambiance);
	// color_clamp(&color);
	// if (surface.r > 0)
	// 	printf("surface: %.2f %.2f %.2f\n", surface.r, surface.g, surface.b);
	return (add_colors(2, surface, reflect));
}
