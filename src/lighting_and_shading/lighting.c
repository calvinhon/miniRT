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

// int	lighting_2()
// {
	
// }

t_color	lighting(t_sphere s, t_light l, t_point p, t_vec4d eye_v)
{
	t_color	effective_c;
	t_vec4d	light_v;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;
	double	light_dot_normal;
	t_vec4d	normal_v;
	t_vec4d	reflect_v;
	double	reflect_dot_eye;

	effective_c = mult_colors(s.material.color, l.color);
	ambient = mult_colors(effective_c, s.material.ambient.color);
	light_v = normalize(subtract_points(l.position, p));
	// printf("light_v: %f, %f, %f\n", light_v.x, light_v.y, light_v.z);
	normal_v = create_vec4d(0, 0, -1);
	// printf("normal: %f, %f, %f\n", normal_v.x, normal_v.y, normal_v.z);
	light_dot_normal = dot(light_v, normal_v);
	diffuse = create_color(0, 0, 0);
	specular = create_color(0, 0, 0);
	if (light_dot_normal >= 0)
	{
		diffuse = scale_color(mult_colors(effective_c, s.material.diffuse), light_dot_normal);
		reflect_v = reflect(negate_vector(light_v), normal_v);
		reflect_dot_eye = dot(reflect_v, eye_v);
		printf("reflect dot eye: %.2f\n", reflect_dot_eye);
		if (reflect_dot_eye > 0)
			specular = scale_color(mult_colors(s.material.specular, l.color),
				pow(reflect_dot_eye, s.material.shininess));
	}
	printf("ambient: %f, %f, %f\n", ambient.r, ambient.g, ambient.b);
	printf("diffuse: %f, %f, %f\n", diffuse.r, diffuse.g, diffuse.b);
	printf("specular: %f, %f, %f\n", specular.r, specular.g, specular.b);
	return (add_colors(3, ambient, diffuse, specular));
}
