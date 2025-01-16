#include "lighting_and_shading.h"

t_vec4d	normal_at(t_sphere s, t_point wrld_p)
{
	t_point	obj_pt;
	t_vec4d	obj_normal;
	t_vec4d	wrld_normal;

	obj_pt = mult_mat4d_pt4d(inverse_mat4d(s.transform), wrld_p);
	obj_normal = subtract_points(obj_pt, create_point(0, 0, 0));
	wrld_normal = mult_mat4d_vec4d(transpose_mat4d(inverse_mat4d(s.transform)), obj_normal);
	wrld_normal.p = 0;
	return (normalize(wrld_normal));
}

t_vec4d	reflect(t_vec4d in, t_vec4d normal)
{
	return (subtract_vectors(in, scale_vector(normal, 2 * dot(in, normal))));
}

t_color	lighting(t_sphere s, t_light l, t_point p, t_vec4d eye_v)
{
	t_color		effective_c;
	t_vec4d		light_v;
	t_material	new;
	double		light_dot_normal;
	double		reflect_dot_eye;
	t_vec4d		normal_v;

	effective_c = mult_colors(s.material.color, l.color);
	new.ambient.color = mult_colors(effective_c, s.material.ambient.color);
	light_v = normalize(subtract_points(l.position, p));
	normal_v = create_vec4d(0, 0, -1);
	light_dot_normal = dot(light_v, normal_v);
	new.diffuse = create_color(0, 0, 0);
	new.specular = create_color(0, 0, 0);
	if (light_dot_normal >= 0)
	{
		new.diffuse = scale_color(mult_colors(effective_c, s.material.diffuse), light_dot_normal);
		reflect_dot_eye = dot(reflect(negate_vector(light_v), normal_v), eye_v);
		if (reflect_dot_eye > 0)
			new.specular = scale_color(mult_colors(s.material.specular, l.color),
				pow(reflect_dot_eye, s.material.shininess));
	}
	return (add_colors(3, new.ambient.color, new.diffuse, new.specular));
}

