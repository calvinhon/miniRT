/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   32parse_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:43:24 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/16 19:51:04 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"


void	parse_ambient(t_minirt *minirt, char *data, size_t *i)
{
	float	intensity;
	t_color	color;

	(*i) += 1;
	intensity = parse_float(data, i);
	color = parse_color(data, i);
	minirt->scene.ambient.intensity = intensity;
	minirt->scene.ambient.color = color;
}

void	parse_camera(t_minirt *minirt, char *data, size_t *i)
{
	t_point		origin;
	t_vector	direction;
	float		fov;


	(*i) += 1;
	origin = parse_point(data, i);
	direction = parse_vector(data, i);
	fov = parse_float(data, i);
	minirt->scene.camera.origin = origin;
	minirt->scene.camera.direction = direction;
	minirt->scene.camera.fov = fov;
}

void	parse_light(t_minirt *minirt, char *data, size_t *i)
{
	t_point	position;
	float	brightness;
	t_color	color;
	size_t	idx;

	(*i) += 1;
	idx = minirt->scene.l++;
	minirt->scene.light[idx].position = parse_point(data, i);
	minirt->scene.light[idx].brightness = parse_float(data, i);
	minirt->scene.light[idx].color = parse_color(data, i);

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
			parse_ambient(minirt, data, i);
		else if (data[start] == 'C')
			parse_camera(minirt, data, &i);
		else if (data[start] == 'l')
			parse_light(minirt, data, &i);
		else
			parse_object(minirt, data, &i);
	}
}

