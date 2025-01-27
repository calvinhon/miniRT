/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:26:43 by nth          #+#    #+#             */
/*   Updated: 2024/10/09 04:07:00 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

int	parse_int(char *data, size_t *i)
{
	int	value;

	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
		(*i)++;
	value = ft_atoi(&data[*i]);
	while (data[*i] && data[*i] != '\t' && data[*i] != ' ' \
			&& data[*i] != '\n' && data[*i] != ',')
		(*i)++;
	return (value);
}

float	parse_float(char *data, size_t *i)
{
	float	value;

	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
		(*i)++;
	value = ft_atof(&data[*i]);
	while (data[*i] && data[*i] != '\t' && data[*i] != ' ' \
			&& data[*i] != '\n' && data[*i] != ',')
		(*i)++;
	return (value);
}

t_color	parse_color(char *data, size_t *i, t_minirt *minirt)
{
	t_color	color;

	color.a = 0.f;
	color.r = parse_int(data, i) / 255.999f;
	color.g = parse_int(data, i) / 255.999f;
	color.b = parse_int(data, i) / 255.999f;
	if (color.r < 0.f || color.r > 1.f || \
	color.g < 0.f || color.g > 1.f || color.b < 0.f || color.b > 1.f)
	{
		free(data);
		printf("Invalid input at position %ld: \n", *i);
		errors(CER_COLOR_VALUE, ER_COLOR_VALUE, minirt);
	}
	return (color);
}

void	parse_ambient(t_minirt *minirt, char *data, size_t *i)
{
	(*i) += 1;
	minirt->ambiance.ratio = parse_float(data, i);
	if (minirt->ambiance.ratio < -0.f || \
		minirt->ambiance.ratio > 1.f)
		return (free(data), errors(CER_AMBIENT_VALUE, \
			ER_AMBIENT_VALUE, minirt));
	minirt->ambiance.is_set = true;
	minirt->ambiance.color = parse_color(data, i, minirt);
	scale_color(&minirt->scene.ambiance, &minirt->ambiance.color, \
		minirt->ambiance.ratio);
}
