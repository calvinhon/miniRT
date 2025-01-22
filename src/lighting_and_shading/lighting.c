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

t_vec4d reflect(t_vec4d *in, t_vec4d *normal)
{
	float in_dot_normal;
	t_vec4d scaled_vec;

	in_dot_normal = dot(*in, *normal);
	scaled_vec = scale_vector(*normal, 2.f * in_dot_normal);
	return (subtract_vectors(*in, scaled_vec));
}

t_color lighting(t_material *m, t_light *l, t_comps *c, bool in_shadow)
{
	t_color effective_color;
	t_vec4d light_v;
	float light_dot_normal;
	float reflect_dot_eye;

	if (m->pattern)
		m->color = pattern_at(c->obj, &c->p, m->pattern);
	effective_color = mult_colors(m->color, l->color);
	c->ambient = scale_color(effective_color, m->ambient_s);
	light_v = normalize(subtract_points(l->position, c->p));
	light_dot_normal = dot(light_v, c->normal_v);
	if (light_dot_normal >= 0 && !in_shadow)
	{
		c->diffuse = scale_color(effective_color, m->diffuse_s);
		c->diffuse = scale_color(c->diffuse, light_dot_normal);
		light_v = negate_vector(light_v);
		reflect_dot_eye = dot(reflect(&light_v, &c->normal_v), c->eye_v);
		if (reflect_dot_eye > 0)
		{
			c->specular = scale_color(l->color,
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
	t_itx_set xs;
	t_itx *h;

	l_v = subtract_points(l->position, *p);
	direction = normalize(l_v);
	r = create_ray(p, &direction);
	xs = local_intersect(s, &r);
	h = get_hit(&xs);
	if (h && h->t < magnitude(l_v)){
		if (h->obj->type == CYLINDER)
			printf("cyl\n");
		return (true);
	}
	return (false);
}

t_color reflected_color(t_scene *s, t_comps *c, int remaining)
{
	t_ray reflect_r;
	t_color color;

	reflect_r = create_ray(&c->over_point, &c->reflect_v);
	color = color_at(s, &reflect_r, remaining - 1);
	return (scale_color(color, c->obj->material.reflect_s));
}

t_color shade_hit(t_scene *s, t_comps *c, int remaining)
{
	t_color lighting_result;
	t_color reflect;
	t_color surface;
	bool in_shadow;
	int i;

	surface = create_color(0, 0, 0);
	reflect = surface;
	i = -1;
	while (++i < s->num_lights)
	{
		in_shadow = is_shadowed(s, &c->over_point, &s->lights[i]);
		lighting_result = lighting(&c->obj->material,
			&s->lights[i], c, in_shadow);
		surface = add_colors(2, surface, lighting_result);
	}
	if (c->obj->material.reflect_s)
		reflect = reflected_color(s, c, remaining);
	// if (s->refract_reflect)
	// {
	// 	refract_reflect = check_for_refref(s, comps, remaining);
	// 	color_add(&color, &color, &refract_reflect);
	// }
	// color_add(&color, &color, &s->ambiance);
	// color_clamp(&color);
	return (add_colors(2, surface, reflect));
}
