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
			

bool	parse_plane_checker(t_material *material, char *data, size_t *i, t_minirt *minirt)
{
	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
			(*i)++;
	if (ft_strncmp(data + (*i), "yes", 3)
		&& ft_strncmp(data + (*i), "no", 22))
		return (minirt->error_code = 4, false);
	if (!ft_strncmp(data + (*i), "yes", 3))
		material->checkered = true;
	else
		material->checkered = false;
	*i += 3;
	minirt->error_code = 0;
	minirt->flt_operations = 1;
	return (true);
}

void	parse_material(t_material *material, char *data, size_t *i, t_minirt *minirt)
{
	while (data[*i] != '\0' && data[*i] != '\n')
	{
		while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
			(*i)++;
		if (!ft_strncmp(data + (*i), "ambient=", 8))
		{
			(*i) += 8;
			material->ambient = parse_float(data, i);
		}
		else if (!ft_strncmp(data + (*i), "diffuse=", 8))
		{
			(*i) += 8;
			material->diffuse = parse_float(data, i);
		}
		else if (!ft_strncmp(data + (*i), "specular=", 9))
		{
			(*i) += 9;
			material->specular = parse_float(data, i);
		}
		else if (!ft_strncmp(data + (*i), "sheen=", 6))
		{
			(*i) += 6;
			material->sheen = parse_float(data, i);
		}
		else if (!ft_strncmp(data + (*i), "reflective=", 11))
		{
			(*i) += 11;
			material->reflective = parse_float(data, i);
		}
		else if (!ft_strncmp(data + (*i), "transparency=", 13))
		{
			(*i) += 13;
			material->transparency = parse_float(data, i);
		}
		else if (!ft_strncmp(data + (*i), "refractive_index=", 17))
		{
			(*i) += 17;
			material->refractive_index = parse_float(data, i);
		}
		else if (!ft_strncmp(data + (*i), "bump_xpm=", 9))
		{
			(*i) += 9;
			parse_bump_xpm(material, data, i, minirt);
		}
		else if (!ft_strncmp(data + (*i), "checker=", 8))
		{
			*i += 8;
			parse_plane_checker(material, data, i, minirt);
		}
		else
		{
			ft_printf("Unknown material field at position %d\n", *i);
			errors(CER_EXPECT_M_TRAIT, ER_EXPECT_M_TRAIT, minirt);
		}
	}
}

void	set_material(t_material *material, char *data, size_t *i, t_minirt *minirt)
{
	material->xordc = (t_color){.v = vec4s_re(0.f, 0.f, 0.f, 0.f)};
	material->ambient = 0.1;
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->sheen = 200;
	material->reflective = 0.0;
	material->transparency = 0.0;
	material->refractive_index = 1.0;
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
