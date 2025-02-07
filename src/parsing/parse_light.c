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

#include "minirt.h"
#include "macros.h"
#include "colors.h"

void parse_light(t_minirt *minirt, char *data, size_t *i)
{
	size_t idx;
	t_color in_color;

	(*i) += 1;
	idx = minirt->scene.light_index++;
	minirt->scene.lights[idx].type = POINT_LIGHT;
	minirt->scene.lights[idx].pos = parse_point(data, i);
	minirt->scene.lights[idx].ratio = parse_float(data, i);
	in_color = parse_color(data, i, minirt);
	minirt->scene.lights[idx].intensity = scale_color(
		&in_color, minirt->scene.lights[idx].ratio);
}

void parse_spotlight(t_minirt *minirt, char *data, size_t *i)
{
	size_t idx;
	t_color in_color;

	(*i) += 2;
	idx = minirt->scene.light_index++;
	minirt->scene.lights[idx].type = SPOT_LIGHT;
	minirt->scene.lights[idx].pos = parse_point(data, i);
	minirt->scene.lights[idx].orientation = parse_vector(data, i);
	is_normalised(&minirt->scene.lights[idx].orientation,
				  *i, minirt);
	minirt->scene.lights[idx].ratio = parse_float(data, i);
	minirt->scene.lights[idx].spot_angle = \
		cosf(parse_float(data, i) * ((float)M_PI / 180.f));
	in_color = parse_color(data, i, minirt);
	minirt->scene.lights[idx].intensity = scale_color(
		&in_color, minirt->scene.lights[idx].ratio);
}
