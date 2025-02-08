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

#include "minirt.h"
#include "macros.h"
#include "colors.h"

static void	parse_pattern_cont1(t_pattern *pattern, char *data, size_t *i, \
	t_minirt *minirt)
{
	if (!ft_strncmp(data + (*i), "CHECKER", 7))
	{
		*i += 7;
		pattern->type = CHECKER;
		pattern->inv_transform = identity_mat();
	}
	else
	{
		ft_printf("Unknown pattern type field at position %d\n", *i);
		ft_printf("data = : %s\n", data + *i);
		errors(CER_EXPECT_M_TRAIT, ER_EXPECT_M_TRAIT, minirt);
	}
}

static void	parse_pattern_cont(t_pattern *pattern, char *data, size_t *i, \
	t_minirt *minirt)
{
	t_mat4d	rot_m;

	if (!ft_strncmp(data + (*i), "STRIPED", 7))
	{
		*i += 7;
		pattern->type = STRIPED;
		rot_m = rotate_mat_z(M_PI / 2);
		pattern->inv_transform = get_inv_tranform_mat4d(rot_m, \
		create_vec4d(0.5f, 0.5f, 0.5f), create_point(0.f, 0.f, 0.f));
	}
	else if (!ft_strncmp(data + (*i), "RING", 4))
	{
		*i += 4;
		pattern->type = RING;
		pattern->inv_transform = scaling_mat(5.0f, 5.0f, 5.0f);
	}
	else
		parse_pattern_cont1(pattern, data, i, minirt);
}

bool	parse_pattern(t_material *material, char *data, \
	size_t *i, t_minirt *minirt)
{
	t_pattern	*pattern;

	pattern = ft_calloc(1, sizeof(t_pattern));
	if (!pattern)
		errors(CER_MALLOC, ER_MALLOC, minirt);
	pattern->a = parse_color(data, i, minirt);
	pattern->b = parse_color(data, i, minirt);
	pattern->p_scale = parse_float(data, i);
	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
		(*i)++;
	if (!ft_strncmp(data + (*i), "GRADIENT", 8))
	{
		*i += 8;
		pattern->type = GRADIENT;
		pattern->inv_transform = scaling_mat(0.5f, 0.5f, 0.5f);
	}
	else
		parse_pattern_cont(pattern, data, i, minirt);
	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
		(*i)++;
	material->pattern = pattern;
	return (true);
}
