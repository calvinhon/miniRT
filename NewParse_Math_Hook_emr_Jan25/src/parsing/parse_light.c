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

void	parse_light(t_minirt *minirt, char *data, size_t *i)
{
	size_t	idx;
	t_color	in_color;

	(*i) += 1;
	idx = minirt->scene.light_count++;
	minirt->scene.lights[idx].type = POINT_LIGHT;
	minirt->scene.lights[idx].pos = parse_point(data, i);
	minirt->scene.lights[idx].ratio = parse_float(data, i);
	in_color = parse_color(data, i);
	scale_color(&minirt->scene.lights[idx].specs.point.intensity,
		&in_color, 	minirt->scene.lights[idx].ratio);

	//// test
	printf("ligt type = %d\n", minirt->scene.lights[idx].type);// test
	// test
	printf("light[%ld].pos = %f, %f, %f\n", idx, minirt->scene.lights[idx].pos.x, minirt->scene.lights[idx].pos.y, minirt->scene.lights[idx].pos.z);// test
	//test
	printf("light[%ld].brightness = %f\n", idx, minirt->scene.lights[idx].ratio);// test
	// test
	printf("light[%ld].intensity = %f, %f, %f\n", idx, 
	minirt->scene.lights[idx].specs.point.intensity.r, 
	minirt->scene.lights[idx].specs.point.intensity.g,
	minirt->scene.lights[idx].specs.point.intensity.b);// test
}

void	parse_spotlight(t_minirt *minirt, char *data, size_t *i)
{
	size_t	idx;
	t_color	in_color;

	(*i) += 2;
	idx = minirt->scene.light_count++;
	minirt->scene.lights[idx].type = SPOT_LIGHT;
	minirt->scene.lights[idx].pos = parse_point(data, i);
	minirt->scene.lights[idx].specs.spot.orientation = parse_vector(data, i);
	is_normalised(&minirt->scene.lights[idx].specs.spot.orientation, *i);
	minirt->scene.lights[idx].ratio = parse_float(data, i);
	minirt->scene.lights[idx].specs.spot.spot_angle = parse_float(data, i);
	minirt->scene.lights[idx].specs.spot.spot_angle *= ((float)M_PI / 180.f);
	in_color = parse_color(data, i);
	scale_color(&minirt->scene.lights[idx].specs.spot.intensity, \
		&in_color, minirt->scene.lights[idx].ratio);

	// test
	printf("ligt type = %d\n", minirt->scene.lights[idx].type);// test
	//test
	printf("light[%ld].pos = %f, %f, %f\n", idx, minirt->scene.lights[idx].pos.x, minirt->scene.lights[idx].pos.y, minirt->scene.lights[idx].pos.z);// test
	// test
	printf("light[%ld].orientation = %f, %f, %f\n", idx, minirt->scene.lights[idx].specs.spot.orientation.x, minirt->scene.lights[idx].specs.spot.orientation.y, minirt->scene.lights[idx].specs.spot.orientation.z);// test
	//test
	printf("light[%ld].ratio = %f\n", idx, minirt->scene.lights[idx].ratio);// test
	//test
	printf("light[%ld].spot_angle = %f\n", idx, minirt->scene.lights[idx].specs.spot.spot_angle);// test
	// test
	printf("light[%ld].intensity = %f, %f, %f\n", idx, minirt->scene.lights[idx].specs.point.intensity.r, minirt->scene.lights[idx].specs.point.intensity.g, minirt->scene.lights[idx].specs.point.intensity.b);// test
	//
}
