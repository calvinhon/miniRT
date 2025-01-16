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
<<<<<<< HEAD

#include "lighting_and_shading.h"

t_vec4d	normal_at(t_object *o, t_point *wrld_p)
=======

#include "minirt.h"

t_vec4d	reflect(t_vec4d *in, t_vec4d *normal)
>>>>>>> 81bd0ab25fe8b8f98353709f500febd6c4c4c223
{
	float	in_dot_normal;
	t_vec4d	scaled_vec;

<<<<<<< HEAD
	obj_pt = mult_mat4d_pt4d(inverse_mat4d(o->transform), *wrld_p);
	obj_normal = subtract_points(obj_pt, create_point(0, 0, 0));
	wrld_normal = mult_mat4d_vec4d(transpose_mat4d(inverse_mat4d(o->transform)), obj_normal);
	wrld_normal.p = 0;
	return (normalize(wrld_normal));
}

t_vec4d	reflect(t_vec4d in, t_vec4d *normal)
{
	return (subtract_vectors(in, scale_vector(*normal, 2 * dot(in, *normal))));
}

t_color	lighting(t_object *o, t_light *l, t_point *p, t_vec4d *eye_v, t_vec4d *normal_v)
{
	t_color		effective_c;
=======
	in_dot_normal = dot(*in, *normal);
	scaled_vec = scale_vector(*normal, 2 * in_dot_normal);
	return (subtract_vectors(*in, scaled_vec));
}

t_color	lighting(t_material *material, t_light *l, t_comps *c, bool in_shadow)
{
	t_color		effective_color;
>>>>>>> 81bd0ab25fe8b8f98353709f500febd6c4c4c223
	t_vec4d		light_v;
	t_material	new;
	double		light_dot_normal;
	double		reflect_dot_eye;

<<<<<<< HEAD
	effective_c = mult_colors(o->material.color, l->color);
	new.ambient.color = mult_colors(effective_c, o->material.ambient.color);
	light_v = normalize(subtract_points(l->position, *p));
	light_dot_normal = dot(light_v, *normal_v);
=======
	effective_color = mult_colors(material->color, l->color);
	new.ambient.color = mult_colors(effective_color, material->ambient.color);
	light_v = normalize(subtract_points(l->position, c->p));
	light_dot_normal = dot(light_v, c->normal_v);
>>>>>>> 81bd0ab25fe8b8f98353709f500febd6c4c4c223
	new.diffuse = create_color(0, 0, 0);
	new.specular = create_color(0, 0, 0);
	if (light_dot_normal >= 0 && !in_shadow)
	{
<<<<<<< HEAD
		new.diffuse = scale_color(mult_colors(effective_c, o->material.diffuse), light_dot_normal);
		reflect_dot_eye = dot(reflect(negate_vector(light_v), normal_v), *eye_v);
		if (reflect_dot_eye > 0)
			new.specular = scale_color(mult_colors(o->material.specular, l->color),
				pow(reflect_dot_eye, o->material.shininess));
=======
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
>>>>>>> 81bd0ab25fe8b8f98353709f500febd6c4c4c223
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
