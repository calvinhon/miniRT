/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   32parse_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:43:24 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/19 00:51:58 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/minirt.h"

void	parse_ambient(t_minirt *minirt, char *data, size_t *i)
{
	(*i) += 1;
	minirt->scene.ambient.intensity = parse_float(data, i);

	minirt->scene.ambient.color = parse_color(data, i);
	//
	printf("A.intensity = %f\n", minirt->scene.ambient.intensity);// test
	printf("A.color = %d, %d, %d\n", minirt->scene.ambient.color.r, \
		minirt->scene.ambient.color.g, minirt->scene.ambient.color.b);// test
	//
}

void	parse_camera(t_minirt *minirt, char *data, size_t *i)
{
	(*i) += 1;
	minirt->scene.camera.origin = parse_point(data, i);
	minirt->scene.camera.direction = parse_vector(data, i);
	minirt->scene.camera.fov = parse_float(data, i);
	//
	printf("C.fov = %f\n", minirt->scene.camera.fov);// test
	//
}

void	parse_light(t_minirt *minirt, char *data, size_t *i)
{
	size_t	idx;

	(*i) += 1;
	idx = minirt->scene.idx_l++;
	minirt->scene.light[idx].position = parse_point(data, i);
	minirt->scene.light[idx].brightness = parse_float(data, i);
	minirt->scene.light[idx].color = parse_color(data, i);
	//
	printf("light[%ld].brightness = %f\n", idx, minirt->scene.light[idx].brightness);// test
	//
}

void	parse_data(t_minirt *minirt, char *data)
{
	size_t	i;
	size_t	start;

	i = 0;
	while (data[i])
	{
		while (data[i] == '\t' || data[i] == ' ' || data[i] == '\n')
			i++;
		if (!data[i])
			break ;
		start = i;
		if (data[start] == 'A')
			parse_ambient(minirt, data, &i);
		else if (data[start] == 'C')
			parse_camera(minirt, data, &i);
		else if (data[start] == 'l' || data[start] == 'L')
			parse_light(minirt, data, &i);
		else
			parse_object(minirt, data, &i);
	}
}

