#include "lighting_and_shading.h"

<<<<<<< HEAD
t_vec4d	normal_at(t_sphere s, t_point wrld_p)
{
	t_point	obj_pt;
	t_vec4d	obj_normal;
	t_vec4d	wrld_normal;
=======
#include "minirt.h"

t_vec4d reflect(t_vec4d *in, t_vec4d *normal)
{
	float in_dot_normal;
	t_vec4d scaled_vec;
>>>>>>> ed472181482a524413cb6122dc67ea5c971f55cf

	obj_pt = mult_mat4d_pt4d(inverse_mat4d(s.transform), wrld_p);
	obj_normal = subtract_points(obj_pt, create_point(0, 0, 0));
	wrld_normal = mult_mat4d_vec4d(transpose_mat4d(inverse_mat4d(s.transform)), obj_normal);
	wrld_normal.p = 0;
	return (normalize(wrld_normal));
}

<<<<<<< HEAD
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
=======
t_color lighting(t_material *m, t_light *l, t_comps *c, bool in_shadow)
{
	t_color effective_color;
	t_vec4d light_v;
	t_material new;
	float light_dot_normal;
	float reflect_dot_eye;

	if (m->pattern)
		effective_color = mult_colors(pattern_at(c->obj, &c->p, m->pattern), l->color);
	else
		effective_color = mult_colors(m->color, l->color);
	new.ambient.color = mult_colors(effective_color, m->ambient.color);
	light_v = normalize(subtract_points(l->position, c->p));
	light_dot_normal = dot(light_v, c->normal_v);
>>>>>>> ed472181482a524413cb6122dc67ea5c971f55cf
	new.diffuse = create_color(0, 0, 0);
	new.specular = create_color(0, 0, 0);
	if (light_dot_normal >= 0)
	{
<<<<<<< HEAD
		new.diffuse = scale_color(mult_colors(effective_c, s.material.diffuse), light_dot_normal);
		reflect_dot_eye = dot(reflect(negate_vector(light_v), normal_v), eye_v);
		if (reflect_dot_eye > 0)
			new.specular = scale_color(mult_colors(s.material.specular, l.color),
				pow(reflect_dot_eye, s.material.shininess));
=======
		new.diffuse = mult_colors(effective_color, m->diffuse);
		new.diffuse = scale_color(new.diffuse, light_dot_normal);
		light_v = negate_vector(light_v);
		reflect_dot_eye = dot(reflect(&light_v, &c->normal_v), c->eye_v);
		if (reflect_dot_eye > 0)
		{
			new.specular = scale_color(mult_colors(m->specular,
				scale_color(l->color, 255)),
				pow(reflect_dot_eye, m->shininess));
		}
>>>>>>> ed472181482a524413cb6122dc67ea5c971f55cf
	}
	return (add_colors(3, new.ambient.color, new.diffuse, new.specular));
}

<<<<<<< HEAD
=======
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
	if (h && h->t < magnitude(l_v))
		return (true);
	return (false);
}

t_color shade_hit(t_scene *s, t_comps *comps, int depth)
{
	t_color lighting_result;
	// t_color		refract_reflect;
	t_color color;
	bool in_shadow;
	int i;

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
>>>>>>> ed472181482a524413cb6122dc67ea5c971f55cf
