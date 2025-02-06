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

t_vec4d reflect(t_vec4d *in, t_vec4d *normal)
{
	float in_dot_normal;
	t_vec4d scaled_vec;

	in_dot_normal = dot_pointers(in, normal);
	scaled_vec = scale_vector(normal, 2.f * in_dot_normal);
	return (subtract_vectors(in, &scaled_vec));
}

t_color lighting(t_material *m, t_light *l, t_comps *c, t_color *ambiance)
{
	t_color effective_color;
	t_vec4d light_v;
	float light_dot_normal;
	float refl_d_eye;

	if (m->pattern)
		m->color = pattern_at(c->obj, &c->p, m->pattern);
	c->diffuse = create_color(0, 0, 0);
	c->specular = create_color(0, 0, 0);
	effective_color = mult_colors(&m->color, &l->intensity);
	printf("m_color: %.2f %.2f %.2f\n", m->color.r, m->color.g, m->color.b);
	c->ambient = mult_colors(&effective_color, ambiance);
	light_v = subtract_points(&l->pos, &c->p);
	light_v = normalize(&light_v);
	// printf("light v: %.2f %.2f %.2f\n", light_v.x, light_v.y, light_v.z);
	// printf("normal v: %.2f %.2f %.2f\n", c->normal_v.x, c->normal_v.y, c->normal_v.z);
	light_dot_normal = dot_pointers(&light_v, &c->normal_v);
	// printf("light dot normal: %.2f\n", light_dot_normal);
	if (light_dot_normal >= 0 && !c->shadowed)
	{
		c->diffuse = scale_color(&effective_color, m->diffuse_s);
		c->diffuse = scale_color(&c->diffuse, light_dot_normal);
		light_v = negate_vector(&light_v);
		refl_d_eye = dot_values(reflect(&light_v, &c->normal_v), c->eye_v);
		if (refl_d_eye > 0)
			c->specular = scale_color(&l->intensity, pow(refl_d_eye,m->shininess) * m->specular_s);
	}
	printf("ambient: %.2f %.2f %.2f\n", c->ambient.r, c->ambient.g, c->ambient.b);
	printf("diffuse: %.2f %.2f %.2f\n", c->diffuse.r, c->diffuse.g, c->diffuse.b);
	printf("specular: %.2f %.2f %.2f\n", c->specular.r, c->specular.g, c->specular.b);
	return (add_colors(3, &c->ambient, &c->diffuse, &c->specular));
}

bool is_shadowed(t_scene *s, t_point *p, t_light *l)
{
	t_vec4d light_v;
	t_vec4d normalized_v;
	t_ray r;
	t_itx_grp xs;
	t_itx *h;

	// printf("point: %.2f %.2f %.2f\n", p->x, p->y, p->z);
	light_v = subtract_points(p, &l->pos);
	normalized_v = normalize(&light_v);
	if (l->type == SPOT_LIGHT && dot_pointers(&l->orientation, &normalized_v) < l->spot_angle)
		return (true);
	light_v = subtract_points(&l->pos, p);
	normalized_v = normalize(&light_v);
	r = create_ray(p, &normalized_v);
	xs = intersect(s, &r);
	h = get_hit(&xs);
	if (h && h->t < magnitude(&light_v))
		return (true);
	return (false);
}

t_color reflected_color(t_scene *s, t_comps *c, int remaining)
{
	t_ray reflect_r;
	t_color color;

	reflect_r = create_ray(&c->over_point, &c->reflect_v);
	color = color_at(s, &reflect_r, remaining - 1);
	return (scale_color(&color, c->obj->material.reflective));
}

t_color shade_hit(t_scene *s, t_comps *c, int remaining)
{
	t_color lighting_result;
	t_color reflect;
	t_color surface;
	t_color	refract;
	int i;

	printf("shade_hit\n");
	surface = create_color(0, 0, 0);
	reflect = surface;
	refract = surface;
	i = -1;
	while (++i < s->num_lights)
	{
		c->shadowed = is_shadowed(s, &c->over_point, &s->lights[i]);
		if (i > 0)
			s->ambiance = create_color(0, 0, 0);
		printf("i: %d\n", i);
		printf("ambiance_color: %.2f %.2f %.2f\n", s->ambiance.r, s->ambiance.g, s->ambiance.b);
		lighting_result = lighting(&c->obj->material,
								   &s->lights[i], c, &s->ambiance);
		surface = add_colors(2, &surface, &lighting_result);
	}
	if (c->obj->material.reflective && s->fr_fl)
		reflect = reflected_color(s, c, remaining);
	if (c->obj->material.refractive && s->fr_fl)
		refract = refracted_color(s, c, remaining);
	printf("surface: %.2f %.2f %.2f\n", surface.r, surface.g, surface.b);
	printf("reflect: %.2f %.2f %.2f\n", reflect.r, reflect.g, reflect.b);
	printf("refract: %.2f %.2f %.2f\n", refract.r, refract.g, refract.b);
	return (add_colors(3, &surface, &reflect, &refract));
}
