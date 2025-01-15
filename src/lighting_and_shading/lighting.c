/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:15:54 by chon              #+#    #+#             */
/*   Updated: 2025/01/13 15:15:54 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4d	reflect(t_vec4d *in, t_vec4d *normal)
{
	float	in_dot_normal;
	t_vec4d	scaled_vec;

	in_dot_normal = dot(*in, *normal);
	scaled_vec = scale_vector(*normal, 2 * in_dot_normal);
	return (subtract_vectors(*in, scaled_vec));
}

t_color	lighting(t_material *material, t_light *l, t_comps *c, bool in_shadow)
{
	t_color		effective_color;
	t_vec4d		light_v;
	t_material	new;
	double		light_dot_normal;
	double		reflect_dot_eye;

	if (in_shadow)
		return (create_color(0.1, 0.1, 0.1));
	effective_color = mult_colors(material->color, l->color);
	new.ambient.color = mult_colors(effective_color, material->ambient.color);
	light_v = normalize(subtract_points(l->position, c->p));
	light_dot_normal = dot(light_v, c->normal_v);
	new.diffuse = create_color(0, 0, 0);
	new.specular = create_color(0, 0, 0);
	if (light_dot_normal >= 0)
	{
		new.diffuse = mult_colors(effective_color, material->diffuse);
		new.diffuse = scale_color(new.diffuse, light_dot_normal);
		light_v = negate_vector(light_v);
		reflect_dot_eye = dot(reflect(&light_v, &c->normal_v), c->eye_v);
		if (reflect_dot_eye > 0)
		{
			new.specular = scale_color(mult_colors(material->specular,
				scale_color(l->color, 255)),
				pow(reflect_dot_eye, material->shininess));
		}
	}
	// printf("ambient: %f %f %f\n", new.ambient.color.r, new.ambient.color.g, new.ambient.color.b);
	// printf("diffuse: %f %f %f\n", new.diffuse.r, new.diffuse.g, new.diffuse.b);
	// printf("specular: %f %f %f\n", new.specular.r, new.specular.g, new.specular.b);
	return (add_colors(3, new.ambient.color, new.diffuse, new.specular));
}

bool	is_shadowed(t_scene *s, t_point *p, t_light *l)
{
	t_vec4d		l_v;
	t_vec4d		direction;
	t_ray		r;
	t_itx_set	xs;
	t_itx		*h;

	l_v = subtract_points(l->position, *p);
	direction = normalize(l_v);
	r = create_ray(p, &direction);
	xs = intersect_world(s, &r);
	h = get_hit(&xs);
	if (h && h->t < magnitude(l_v))
		return (true);
	return (false);
}


t_color	shade_hit(t_scene *s, t_comps *comps, int depth)
{
	t_color		lighting_result;
	// t_color		refract_reflect;
	t_color		color;
	bool		in_shadow;
	int			i;

	color = create_color(0, 0, 0);
	i = -1;
	while (++i < s->num_lights)
	{
		in_shadow = is_shadowed(s, &comps->over_point, &s->lights[i]);
		lighting_result = lighting(&comps->obj->material,
				&s->lights[i], comps, in_shadow);
		color = add_colors(2, color, lighting_result);
	}
	(void)depth;
	// if (s->refract_reflect)
	// {
	// 	refract_reflect = check_for_refref(s, comps, depth);
	// 	color_add(&color, &color, &refract_reflect);
	// }
	// color_add(&color, &color, &s->ambiance);
	// color_clamp(&color);
	// printf("color: %f %f %f\n", color.r, color.g, color.b);
	return (color);
}
