/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   322parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:43:24 by honguyen          #+#    #+#             */
<<<<<<< HEAD:src/parsing/322parse_utils.c
/*   Updated: 2025/01/13 16:29:04 by marvin           ###   ########.fr       */
=======
/*   Updated: 2025/01/16 16:09:54 by chon             ###   ########.fr       */
>>>>>>> ed472181482a524413cb6122dc67ea5c971f55cf:src/parsing_h/322parse_utils.c
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int parse_int(char *data, size_t *i)
{
	int value;

	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
		(*i)++;
	value = ft_atoi(&data[*i]);
	while (data[*i] && data[*i] != '\t' && data[*i] != ' ' && data[*i] != '\n' && data[*i] != ',')
		(*i)++;
	return (value);
}

float parse_float(char *data, size_t *i)
{
	float value;

	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
		(*i)++;
	value = ft_atof(&data[*i]);
	while (data[*i] && data[*i] != '\t' && data[*i] != ' ' && data[*i] != '\n' && data[*i] != ',')
		(*i)++;
	return (value);
}

t_point parse_point(char *data, size_t *i)
{
	t_point point;

	point.x = parse_float(data, i);
	point.y = parse_float(data, i);
	point.z = parse_float(data, i);
	point.p = 1.0;
	return (point);
}

<<<<<<< HEAD:src/parsing/322parse_utils.c
t_vec4d	parse_vector(char *data, size_t *i)
{
	t_vec4d	vector;
=======
t_vector parse_vector(char *data, size_t *i)
{
	t_vector vector;
>>>>>>> ed472181482a524413cb6122dc67ea5c971f55cf:src/parsing_h/322parse_utils.c

	vector.x = parse_float(data, i);
	vector.y = parse_float(data, i);
	vector.z = parse_float(data, i);
	vector.p = 0.0;
	return (vector);
}

t_color parse_color(char *data, size_t *i)
{
	t_color color;

	color.r = parse_int(data, i);
	color.g = parse_int(data, i);
	color.b = parse_int(data, i);
	color.t = 0;
	return (color);
}
