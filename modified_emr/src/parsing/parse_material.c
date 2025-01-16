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

static bool	parse_traits_extension(char *field, char *value,
	t_material *obj_material, t_minirt *minirt)
{
	float	temp;

	temp = ft_atof(value, minirt);
	if (!ft_strncmp(field, "reflective", ft_strlen(field)) && temp >= 0.f
		&& temp <= 1.f)
		obj_material->reflective = temp;
	else if (!ft_strncmp(field, "transparency", ft_strlen(field)) && temp
		>= 0.f && temp <= 1.f)
		obj_material->transparency = temp;
	else if (!ft_strncmp(field, "refractive_index", ft_strlen(field)) && temp
		>= 0.f && temp <= 2.f)
		obj_material->refractive_index = temp;
	else if (!ft_strncmp(field, "bump_xpm", ft_strlen(field)))
		return (parse_bump_xpm(obj_material, minirt, value));
	else if (!ft_strncmp(field, "checker", ft_strlen(field)))
		return (parse_plane_checker(obj_material, minirt, value));
	else
		return (false);
	if (minirt->error_code == 2 || minirt->flt_operations == 0)
		return (false);
	return (true);
}

static bool	parse_traits(char *field, char *value, t_material *obj_material,
	t_minirt *minirt)
{
	float	temp;

	temp = ft_atof(value, minirt);
	if (!ft_strncmp(field, "ambient", ft_strlen(field)) && temp
		>= 0.f && temp <= 1.f)
		obj_material->ambient = temp;
	else if (!ft_strncmp(field, "specular", ft_strlen(field)) && temp
		>= 0.f && temp <= 1.f)
		obj_material->specular = temp;
	else if (!ft_strncmp(field, "diffuse", ft_strlen(field)) && temp
		>= 0.f && temp <= 1.f)
		obj_material->diffuse = temp;
	else if (!ft_strncmp(field, "sheen", ft_strlen(field)) && temp
		>= 0.f && temp <= 200.f)
		obj_material->sheen = temp;
	else
		return (parse_traits_extension(field, value, obj_material, minirt));
	if (minirt->error_code == 2 || minirt->flt_operations == 0)
		return (false);
	return (true);
}

static bool	check_material_fields(t_material *obj_material,
	char *material_field, t_minirt *minirt, int line)
{
	t_split	split;
	bool	ret;

	split = ft_split(material_field, "=\n\r");
	if (split.wordcount != 2)
		return (parse_warn_msg(ER_M_FORMAT, ER_EXPECT_M ER_EM2, line, false),
			destroy_2d_arr(split.array), false);
	ret = parse_traits(split.array[0], split.array[1], obj_material, minirt);
	if (!ret && minirt->error_code == 3)
		return (parse_warn_msg(ER_M_BUMP_FORMAT, ER_EXPECT_XPM, line, true),
			destroy_2d_arr(split.array), true);
	else if (!ret && (minirt->error_code == 2 || minirt->flt_operations
			== 0))
		return (parse_warn_msg(ER_M_VALUE, ER_EXPECT_FLOAT, line, true),
			destroy_2d_arr(split.array), true);
	else if (!ret && minirt->error_code == 4)
		return (parse_warn_msg(ER_M_CHECKER, ER_EXPECT_CHECKER, line, true),
			destroy_2d_arr(split.array), true);
	else if (!ret)
		return (parse_warn_msg(ER_M_FORMAT, ER_EXPECT_M_TRAIT ER_EMT2,
				line, true), destroy_2d_arr(split.array), true);
	return (destroy_2d_arr(split.array), true);
}

bool	parse_material(t_material *obj_material, char **material_fields,
	t_minirt *minirt, int line)
{
	t_split	traits;
	t_split	split;
	size_t	i;

	if (!material_fields || !material_fields[0]
		|| ft_strncmp(material_fields[0], "M", 1))
		return (false);
	split = ft_split(material_fields[1], ",\n\r");
	if (split.wordcount > 7)
		return (parse_err_msg(ER_M_FORMAT, ER_EXPECT_M, line), false);
	i = 0;
	destroy_2d_arr(split.array);
	traits = ft_split(material_fields[1], ",");
	while (i < traits.wordcount)
	{
		if (!check_material_fields(obj_material, traits.array[i], minirt,
				line))
			return (destroy_2d_arr(traits.array), false);
		i++;
	}
	return (destroy_2d_arr(traits.array), true);
}
