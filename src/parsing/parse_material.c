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

bool	parse_plane_checker(t_material *material, char *data, \
	size_t *i, t_minirt *minirt)
{
	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
		(*i)++;
	if (ft_strncmp(data + (*i), "yes", 3) && ft_strncmp(data + (*i), "no", 22))
		return (minirt->error_code = 4, false);
	if (!ft_strncmp(data + (*i), "yes", 3))
	{
		*i += 3;
		material->checkered = true;
	}
	else
	{
		*i += 2;
		material->checkered = false;
	}
	minirt->error_code = 0;
	minirt->flt_operations = 1;
	return (true);
}

void	parse_material_cont1(t_material *material, char *data, \
	size_t *i, t_minirt *minirt)
{
	if (!ft_strncmp(data + (*i), "bump_xpm=", 9))
	{
		(*i) += 9;
		parse_bump_xpm(material, data, i, minirt);
	}
	else if (!ft_strncmp(data + (*i), "checker=", 8))
	{
		*i += 8;
		parse_plane_checker(material, data, i, minirt);
	}
	else if (!ft_strncmp(data + (*i), "refractive=", 11))
	{
		(*i) += 11;
		material->refractive = parse_float(data, i);
	}
	else
	{
		ft_printf("Unknown material field at position %d:\n", *i);
		ft_printf("data: %s\n", data + *i);
		errors(CER_EXPECT_M_TRAIT, ER_EXPECT_M_TRAIT, minirt);
	}
}

void	parse_material_cont(t_material *material, char *data, \
	size_t *i, t_minirt *minirt)
{
	if (!ft_strncmp(data + (*i), "reflective=", 11))
	{
		(*i) += 11;
		material->reflective = parse_float(data, i);
	}
	else if (!ft_strncmp(data + (*i), "pattern=", 8))
	{
		*i += 8;
		parse_pattern(material, data, i, minirt);
	}
	else if (!ft_strncmp(data + (*i), "sheen=", 6))
	{
		(*i) += 6;
		material->shininess = parse_float(data, i);
	}
	else if (!ft_strncmp(data + (*i), "transparency=", 13))
	{
		(*i) += 13;
		material->transparency = parse_float(data, i);
	}
	else
		parse_material_cont1(material, data, i, minirt);
}

void	parse_material(t_material *material, char *data,
					size_t *i, t_minirt *minirt)
{
	while (data[*i] != '\0' && data[*i] != '\n')
	{
		while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
			(*i)++;
		if (!ft_strncmp(data + (*i), "ambient=", 8))
		{
			(*i) += 8;
			material->ambient_s = parse_float(data, i);
		}
		else if (!ft_strncmp(data + (*i), "diffuse=", 8))
		{
			(*i) += 8;
			material->diffuse_s = parse_float(data, i);
		}
		else if (!ft_strncmp(data + (*i), "specular=", 9))
		{
			(*i) += 9;
			material->specular_s = parse_float(data, i);
		}
		else
			parse_material_cont(material, data, i, minirt);
	}
}

void	set_material(t_material *material, char *data, size_t *i, \
	t_minirt *minirt)
{
	material->ambient_s = 0.1;
	material->diffuse_s = 0.9;
	material->specular_s = 0.9;
	material->shininess = 200;
	material->reflective = 0.0;
	material->transparency = 0.0;
	material->refractive = 1.0;
	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
		(*i)++;
	if (data[*i] == 'M')
	{
		(*i)++;
		parse_material(material, data, i, minirt);
	}
	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
		(*i)++;
}
