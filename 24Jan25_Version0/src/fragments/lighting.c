/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:18:23 by nth          #+#    #+#             */
/*   Updated: 2025/01/14 14:27:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "colors.h"
#include "macros.h"

static inline void	plane_pattern_blend(t_color *ec,
			const t_itx_data *comps, const t_color *intens)
{
	const t_material	*mater = &comps->obj->material;
	t_vec4s				local_p;

	cross_mat4s_vec4s(&comps->obj->inv_transform,
		&comps->over_point, &local_p);
	if ((int)(fabsf(floorf(local_p.x)) + fabsf(floorf(local_p.y))
		+ fabsf(floorf(local_p.z))) % 2)
		blend_color(ec, &mater->color, intens);
	else
		blend_color(ec, &mater->xordc, intens);
}

static void	lighting_init(t_material_colors *mat_colors, t_light *light,
			t_itx_data *comps, t_material *material)
{
	if (light->type == SPOT_LIGHT)
		mat_colors->intensity = light->specs.spot.intensity;
	else
		mat_colors->intensity = light->specs.point.intensity;
	if (comps->obj->type == PLANE && material->checkered)
		plane_pattern_blend(&mat_colors->effective_color, comps,
			&mat_colors->intensity);
	else
		blend_color(&mat_colors->effective_color, &material->color,
			&mat_colors->intensity);
	scale_color(&mat_colors->ambient, &mat_colors->effective_color,
		material->ambient);
}

static void	lighting_extension(t_material_colors *mc, t_material *material,
			t_vec4s *light_v, t_itx_data *comps)
{
	float	reflect_eye_dot;
	float	factor;
	t_vec4s	reflect_v;
	float	hidden_spotlight_intensity;

	hidden_spotlight_intensity = light_v->w;
	light_v->w = 0.f;
	negate_vec4s(light_v);
	reflect_v = reflect(light_v, &comps->normalv);
	reflect_eye_dot = dot_vec4s_re(&reflect_v, &comps->eyev);
	if (reflect_eye_dot <= 0)
		ini_color(&mc->specular, 0.0, 0.0, 0.0);
	else
	{
		factor = powf(reflect_eye_dot, material->sheen);
		if (mc->light_type == SPOT_LIGHT)
			factor *= hidden_spotlight_intensity;
		scale_color(&mc->specular, &mc->intensity,
			material->specular * factor);
	}
	add_color(&mc->return_color, &mc->ambient, &mc->diffuse);
	add_color(&mc->return_color, &mc->return_color, &mc->specular);
}

t_color	lighting(t_itx_data *comps, t_material *material, t_light *light,
			bool in_shadow)
{
	t_vec4s				light_v;
	t_material_colors	mat_colors;
	float				light_dot_normal;
	float				spot_intensity;

	lighting_init(&mat_colors, light, comps, material);
	sub_vec4s(&light_v, &light->pos, &comps->over_point);
	normalize_vec4s(&light_v);
	dot_vec4s(&light_dot_normal, &light_v, &comps->normalv);
	if (light_dot_normal < EPSILON || in_shadow)
		return (check_for_texture(comps, material, &mat_colors),
			mat_colors.ambient);
	mat_colors.light_type = light->type;
	if (light->type == SPOT_LIGHT && !in_shadow)
	{
		spot_intensity = get_spot_light_intensity(light, light_v);
		scale_color(&mat_colors.effective_color, &mat_colors.effective_color,
			spot_intensity);
		light_v.w = spot_intensity;
	}
	scale_color(&mat_colors.diffuse, &mat_colors.effective_color,
		material->diffuse * light_dot_normal);
	lighting_extension(&mat_colors, material, &light_v, comps);
	return (mat_colors.return_color);
}

t_color	shade_hit(t_scene *scene, t_itx_data *comps, int depth)
{
	t_color		lighting_result;
	t_color		refract_reflect;
	t_color		return_color;
	bool		in_shadow;
	int			i;

	ini_color(&return_color, 0.f, 0.f, 0.f);
	i = -1;
	while (++i < scene->num_lights)
	{
		in_shadow = is_shadowed(scene, &comps->over_point, &scene->lights[i]);
		lighting_result = lighting(comps, &comps->obj->material,
				&scene->lights[i], in_shadow);
		add_color(&return_color, &return_color, &lighting_result);
	}
	if (scene->refract_reflect)
	{
		refract_reflect = check_for_refref(scene, comps, depth);
		add_color(&return_color, &return_color, &refract_reflect);
	}
	add_color(&return_color, &return_color, &scene->ambiance);
	clamp_color(&return_color);
	return (return_color);
}
