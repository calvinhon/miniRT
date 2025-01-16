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

#include "lighting_and_shading.h"

t_vec4d	normal_at(t_object *o, t_point *wrld_p)
{
	t_point	obj_pt;
	t_vec4d	obj_normal;
	t_vec4d	wrld_normal;

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
	t_vec4d		light_v;
	t_material	new;
	double		light_dot_normal;
	double		reflect_dot_eye;

	effective_c = mult_colors(o->material.color, l->color);
	new.ambient.color = mult_colors(effective_c, o->material.ambient.color);
	light_v = normalize(subtract_points(l->position, *p));
	light_dot_normal = dot(light_v, *normal_v);
	new.diffuse = create_color(0, 0, 0);
	new.specular = create_color(0, 0, 0);
	if (light_dot_normal >= 0)
	{
		new.diffuse = scale_color(mult_colors(effective_c, o->material.diffuse), light_dot_normal);
		reflect_dot_eye = dot(reflect(negate_vector(light_v), normal_v), *eye_v);
		if (reflect_dot_eye > 0)
			new.specular = scale_color(mult_colors(o->material.specular, l->color),
				pow(reflect_dot_eye, o->material.shininess));
	}
	return (add_colors(3, new.ambient.color, new.diffuse, new.specular));
}

