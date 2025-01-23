/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:47:21 by nth          #+#    #+#             */
/*   Updated: 2024/11/20 10:25:45 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "colors.h"
#include "macros.h"

t_color	reflected_color(t_scene *scene, t_itx_data *comps, int depth)
{
	t_ray		r;
	t_color		reflected_color;
	t_vec4s		reflectv;
	t_vec4s		reflect_origin;
	t_vec4s		offset;

	ini_color(&reflected_color, 0.0, 0.0, 0.0);
	if (depth <= 0 || comps->obj->material.reflective <= 0.0)
		return (reflected_color);
	reflectv = comps->reflectv;
	scale_vec4s(&offset, comps->normalv, EPSILON);
	add_vec4s(&reflect_origin, &comps->over_point, &offset);
	ray_create(&r, &reflect_origin, &reflectv);
	reflected_color = color_at(scene, &r, depth - 1);
	scale_color(&reflected_color, &reflected_color,
		comps->obj->material.reflective);
	return (reflected_color);
}

static void	check_for_refref_init(t_itx_data *comps, t_color *return_color)
{
	ini_color(return_color, 0.0, 0.0, 0.0);
	if (comps->obj->material.reflective > 0.0f)
		scale_color(return_color, return_color,
			1.0f - comps->obj->material.reflective);
	if (comps->obj->material.transparency > 0.0f)
		scale_color(return_color, return_color,
			1.0f - comps->obj->material.transparency);
}

t_color	check_for_refref(t_scene *scene, t_itx_data *comps, int depth)
{
	double		schlick_value;
	t_color		reflection_result;
	t_color		refraction_result;
	t_color		return_color;

	reflection_result = reflected_color(scene, comps, depth);
	refraction_result = refracted_color(scene, comps, depth);
	check_for_refref_init(comps, &return_color);
	if (comps->obj->material.reflective > 0.0f
		&& comps->obj->material.transparency > 0.0f)
	{
		schlick_value = schlick(comps);
		scale_color(&reflection_result,
			&reflection_result, 1.0f - schlick_value);
		scale_color(&reflection_result, &reflection_result, schlick_value);
	}
	if (comps->obj->material.reflective > 0.0f)
		add_color(&return_color, &return_color, &reflection_result);
	if (comps->obj->material.transparency > 0.0f)
		add_color(&return_color, &return_color, &refraction_result);
	return (return_color);
}
