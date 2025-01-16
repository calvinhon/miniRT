/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:22:24 by nth          #+#    #+#             */
/*   Updated: 2024/10/16 13:10:35 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool	parse_spot_light_color(const t_split *fields, int curr_line,
			t_scene *scene, t_minirt *minirt)
{
	t_light	*light;
	t_color	parsed_color;

	light = &scene->lights[scene->num_lights];
	if (!parse_single_f(&light->ratio, fields->array[3], minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	if (light->ratio < -0.f || light->ratio > 1.f)
		return (parse_err_msg(ER_LIGHT_VALUE, ER_EXPECT_F_RANGE,
				curr_line), destroy_2d_arr(fields->array), false);
	if (!parse_single_f(&light->specs.spot.spot_angle, fields->array[4],
			minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	if (light->specs.spot.spot_angle < 10.f || light->specs.spot.spot_angle
		> 90.f)
		return (parse_err_msg(ER_LIGHT_VALUE, ER_EXPECT_FLOAT, curr_line),
			destroy_2d_arr(fields->array), false);
	light->specs.spot.spot_angle *= ((float)M_PI / 180.f);
	if (!parse_color(&parsed_color,
			fields->array[5], curr_line))
		return (destroy_2d_arr(fields->array), false);
	scale_color(&light->specs.spot.intensity, \
		&parsed_color, light->ratio);
	return (true);
}

bool	parse_spot_light(t_minirt *minirt, const t_split *fields,
			int curr_line)
{
	t_light	*light;

	light = &minirt->scene.lights[minirt->scene.num_lights];
	if (minirt->scene.num_lights >= LIGHTS_MAX)
		return (parse_warn_msg(ER_MAX_LIGHTS, NULL, curr_line, true),
			destroy_2d_arr(fields->array), true);
	if (fields->wordcount != 6)
		return (parse_err_msg(ER_LIGHT_FORMAT, ER_EXPECT_TYPE_SL ER_ESL,
				curr_line), destroy_2d_arr(fields->array), false);
	if (!parse_vec4p(&light->pos, fields->array[1], minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	if (!parse_vec4v(&light->specs.spot.orientation, fields->array[2],
			minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	if (!parse_spot_light_color(fields, curr_line, &minirt->scene, minirt))
		return (false);
	negate_vec4s(&light->specs.spot.orientation);
	is_normalised(&light->specs.spot.orientation, curr_line);
	light->type = SPOT_LIGHT;
	minirt->scene.num_lights++;
	return (destroy_2d_arr(fields->array), true);
}

bool	parse_point_light_color(const t_split *fields, int curr_line,
			t_scene *scene)
{
	t_light	*curr_light;
	t_color	parsed_color;

	curr_light = &scene->lights[scene->num_lights];
	if (!parse_color(&parsed_color,
			fields->array[3], curr_line))
		return (destroy_2d_arr(fields->array), false);
	scale_color(&curr_light->specs.point.intensity, \
		&parsed_color, curr_light->ratio);
	scene->num_lights++;
	return (true);
}

bool	parse_light(t_minirt *minirt, const t_split *fields, int curr_line)
{
	t_light	*light;
	float	temp;

	light = &minirt->scene.lights[minirt->scene.num_lights];
	if (minirt->scene.num_lights >= LIGHTS_MAX)
		return (parse_warn_msg(ER_MAX_LIGHTS, NULL, curr_line, true),
			destroy_2d_arr(fields->array), true);
	if (fields->wordcount != 4)
		return (parse_err_msg(ER_LIGHT_FORMAT, ER_EXPECT_TYPE_L,
				curr_line), destroy_2d_arr(fields->array), false);
	if (!parse_vec4p(&light->pos, fields->array[1], minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	temp = ft_atof(fields->array[2], minirt);
	if (minirt->error_code == 2)
		return (parse_err_msg(ER_LIGHT_VALUE, ER_EXPECT_FLOAT, curr_line),
			destroy_2d_arr(fields->array), false);
	if (temp < -0.f || temp > 1.f)
		return (parse_err_msg(ER_LIGHT_VALUE, ER_EXPECT_F_RANGE,
				curr_line),
			destroy_2d_arr(fields->array), false);
	light->ratio = temp;
	if (!parse_point_light_color(fields, curr_line, &minirt->scene))
		return (false);
	light->type = POINT_LIGHT;
	return (destroy_2d_arr(fields->array), true);
}
