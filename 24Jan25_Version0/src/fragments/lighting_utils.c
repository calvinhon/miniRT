/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:20:27 by nth          #+#    #+#             */
/*   Updated: 2025/01/14 14:27:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "colors.h"
#include "macros.h"

bool	is_spot_light_shadowed(t_light *light, t_vec4s *v)
{
	float	cos_align;
	float	outer_cone_cos;
	float	inner_cone_cos;
	float	angle_attenuation;
	float	delta_cos;

	cos_align = dot_vec4s_re(v, &light->specs.spot.orientation);
	outer_cone_cos = cosf(light->specs.spot.spot_angle);
	inner_cone_cos = cosf(light->specs.spot.spot_angle * 0.75f);
	if (cos_align < outer_cone_cos)
		return (true);
	if (cos_align < inner_cone_cos)
	{
		delta_cos = inner_cone_cos - outer_cone_cos;
		angle_attenuation = powf((cos_align - outer_cone_cos) / delta_cos,
				SPOTLIGHT_FALLOFF);
		if (angle_attenuation < 0.1f)
			return (true);
	}
	return (false);
}

float	get_spot_light_intensity(t_light *light, t_vec4s light_v)
{
	float	angle_attenuation;
	float	cos_align;
	float	outer_cone_cos;
	float	inner_cone_cos;
	float	delta_cos;

	if (light->type == SPOT_LIGHT)
	{
		cos_align = dot_vec4s_re(&light_v,
				&light->specs.spot.orientation);
		outer_cone_cos = cosf(light->specs.spot.spot_angle);
		inner_cone_cos = cosf(light->specs.spot.spot_angle * 0.75f);
		if (cos_align < outer_cone_cos)
			return (0.0f);
		if (cos_align >= inner_cone_cos)
			return (1.0f);
		delta_cos = inner_cone_cos - outer_cone_cos;
		if (delta_cos < 0.001f)
			return (_RT_MIN_INTENSITY);
		angle_attenuation = powf((cos_align - outer_cone_cos)
				/ delta_cos, SPOTLIGHT_FALLOFF);
		return (fmax(angle_attenuation, _RT_MIN_INTENSITY));
	}
	return (0.0f);
}

bool	is_shadowed(t_scene *scene, t_vec4s *point, t_light *light)
{
	t_vec4s		v;
	t_ray		r;
	t_itx_grp	xs;
	t_itx		*itx;
	t_vec4s		hit_pos;

	sub_vec4s(&v, &light->pos, point);
	if (light->type == SPOT_LIGHT && is_spot_light_shadowed(light, &v))
		return (true);
	ray_create(&r, point, &v);
	cast_shadow_ray(scene, &r, &xs);
	itx = get_hit(&xs);
	if (!itx)
		return (false);
	ray_position(&hit_pos, &r, itx->t);
	sub_vec4s(&hit_pos, &hit_pos, point);
	if (magnitude_vec4s_re(hit_pos) < magnitude_vec4s_re(v))
		return (true);
	return (false);
}

void	cast_shadow_ray(t_scene *w, t_ray *r, t_itx_grp *xs)
{
	int			i;
	int			itx_occured;

	i = -1;
	xs->count = 0;
	itx_occured = 0;
	while (++i < w->num_shapes)
	{
		if (xs->count >= _RT_MAX_ITX || itx_occured > 2)
			break ;
		if (w->shapes[i].type == SPHERE)
			itx_occured += intersect_sphere(r, &w->shapes[i], xs);
		else if (w->shapes[i].type == PLANE)
			itx_occured += intersect_plane(r, &w->shapes[i], xs);
		else if (w->shapes[i].type == CYLINDER)
			itx_occured += intersect_cylinder(r, &w->shapes[i], xs);
		else if (w->shapes[i].type == CUBIC)
			itx_occured += intersect_cube(r, &w->shapes[i], xs);
		else if (w->shapes[i].type == CONE)
			itx_occured += intersect_cone(r, &w->shapes[i], xs);
	}
}

void	check_for_texture(t_itx_data *comps, t_material *material,
			t_material_colors *mat_colors)
{
	t_vec4s	scaled_normal;

	if (comps->obj->material.fra_tex)
	{
		scaled_normal = scale_vec4s_re(comps->normalv,
				material->ambient * material->ambient);
		add_vec4s(&mat_colors->ambient.v, &mat_colors->ambient.v,
			&scaled_normal);
		clamp_color(&mat_colors->ambient);
	}
}
