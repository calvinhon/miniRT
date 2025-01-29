/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:02:53 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 18:40:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

static void	parse_pattern_cont(t_pattern *pattern, char *data, size_t *i, \
		t_minirt *minirt)
{
	if  (!ft_strncmp(data + (*i), "STRIPED", 7))
	{
		*i += 7;
		pattern->type = STRIPED;
		pattern->transform =  mult_n_mat4d(2, rotate_mat_z(PI / 2), \
			scaling_mat(0.5, 0.5, 0.5));;
	}
	else if (!ft_strncmp(data + (*i), "RING", 4))
	{
		*i += 4;
		pattern->type = RING;
		pattern->transform = scaling_mat(1, 1, 1);
	}
	else
	{
		ft_printf("Unknown pattern type field at position %d\n", *i);
		errors(CER_EXPECT_M_TRAIT, ER_EXPECT_M_TRAIT, minirt);
	}
}

bool	parse_pattern(t_material *material, char *data, \
	size_t *i, t_minirt *minirt)
{
	t_pattern	pattern;

	pattern.a = parse_color(data, i, minirt);
	pattern.b = parse_color(data, i, minirt);
	pattern.p_scale = parse_float(data, i);
	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
		(*i)++;
	if (!ft_strncmp(data + (*i), "GRADIENT", 8))
	{
		*i += 8;
		pattern.type= GRADIENT;
		pattern.transform = scaling_mat(10, 10, 10);
	}
	else if (!ft_strncmp(data + (*i), "CHECKER", 7))
	{
		*i += 7;
		pattern.type = CHECKER;
		pattern.transform = identity_mat();	
	}
	else
		parse_pattern_cont(&pattern, data, i, minirt);
	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
		(*i)++;
	pattern.inv_transform = inverse_mat4d(pattern.transform);
	material->pattern = pattern;
	//
	printf("pattern color: %f %f %f\n", pattern.a.r, pattern.a.g, pattern.a.b);
	printf("pattern color: %f %f %f\n", pattern.b.r, pattern.b.g, pattern.b.b);
	printf("pattern scale: %f\n", pattern.p_scale);
	printf("pattern type: %d\n", pattern.type);
	//
	return (true);
}
