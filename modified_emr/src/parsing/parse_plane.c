/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:08:31 by nth          #+#    #+#             */
/*   Updated: 2025/01/14 18:20:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

static void	material_init(t_material *material, const t_split *fields,
	t_minirt *minirt, int curr_line)
{
	material->xordc = (t_color){.v = vec4s_re(0.f, 0.f, 0.f, 0.f)};
	material->ambient = 0.1;
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->sheen = 200;
	material->reflective = 0.0;
	material->transparency = 0.0;
	material->refractive_index = 1.0;
	if (fields->wordcount == 6 && parse_material(material, &fields->array[4],
			minirt, curr_line))
		return ;
}

bool	parse_plane_checker(t_material *obj_mat, t_minirt *minirt,
		char *is_checker)
{
	if (ft_strncmp(is_checker, "yes", ft_strlen(is_checker))
		&& ft_strncmp(is_checker, "no", ft_strlen(is_checker)))
		return (minirt->error_code = 4, false);
	if (!ft_strncmp(is_checker, "yes", ft_strlen(is_checker)))
		obj_mat->checkered = true;
	else
		obj_mat->checkered = false;
	minirt->error_code = 0;
	minirt->flt_operations = 1;
	return (true);
}

bool	parse_plane(t_minirt *minirt, const t_split *fields, int curr_line)
{
	t_object	*pl;

	if (minirt->scene.num_shapes == SHAPES_MAX)
		return (destroy_2d_arr(fields->array),
			parse_warn_msg(ER_MAX_SHAPES, NULL, curr_line, true), true);
	pl = &minirt->scene.shapes[minirt->scene.num_shapes++];
	if (fields->wordcount < 4 || fields->wordcount > 6)
		return (parse_err_msg(ER_OBJ_FORMAT, ER_E_T_PL,
				curr_line), destroy_2d_arr(fields->array), false);
	pl->type = PLANE;
	if (!parse_vec4p(&pl->trans, fields->array[1], minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	if (!parse_vec4v(&pl->orientation, fields->array[2], minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	is_normalised(&pl->orientation, curr_line);
	if (!parse_color(&pl->material.color, fields->array[3], curr_line))
		return (destroy_2d_arr(fields->array), false);
	material_init(&pl->material, fields, minirt, curr_line);
	pl->scale = vec4s_re(1, 1, 1, 1);
	pl->rot = rt_extract_rot_vertical(pl->orientation);
	pl->inv_transform = get_inv_tranform_mat4s(pl->rot,
			pl->scale, pl->trans);
	transpose_mat4s(&pl->inv_transform, &pl->transposed_inverse);
	return (pl->center.w = 1.f, destroy_2d_arr(fields->array), true);
}
