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
	t_mat4d	transposed;

	obj_pt = mult_mat4d_pt4d(o->inv_transform, *wrld_p);
	obj_normal = subtract_points(obj_pt, create_point(0, 0, 0));
	transposed = transpose_mat4d(o->inv_transform);
	wrld_normal = mult_mat4d_vec4d(transposed, obj_normal);
	wrld_normal.p = 0;
	return (normalize(wrld_normal));
}

t_vec4d	reflect(t_vec4d *in, t_vec4d *normal)
{
	float	in_dot_normal;
	t_vec4d	scaled_vec;

	in_dot_normal = dot(*in, *normal);
	scaled_vec = scale_vector(*normal, 2 * in_dot_normal);
	return (subtract_vectors(*in, scaled_vec));
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
		new.diffuse = mult_colors(effective_c, o->material.diffuse);
		new.diffuse = scale_color(new.diffuse, light_dot_normal);
		light_v = negate_vector(light_v);
		reflect_dot_eye = dot(reflect(&light_v, normal_v), *eye_v);
		if (reflect_dot_eye > 0)
		{
			// printf("%f\n", reflect_dot_eye);
			new.specular = scale_color(mult_colors(o->material.specular, scale_color(l->color, 255)),
				pow(reflect_dot_eye, o->material.shininess));
			// printf("specular: %f %f %f\n", new.specular.r, new.specular.g, new.specular.b);
		}
	}
	// printf("ambient: %f %f %f\n", new.ambient.color.r, new.ambient.color.g, new.ambient.color.b);
	// printf("diffuse: %f %f %f\n", new.diffuse.r, new.diffuse.g, new.diffuse.b);
	// printf("specular: %f %f %f\n", new.specular.r, new.specular.g, new.specular.b);
	return (add_colors(3, new.ambient.color, new.diffuse, new.specular));
}

