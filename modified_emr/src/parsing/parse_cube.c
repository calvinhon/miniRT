/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:38:04 by nth          #+#    #+#             */
/*   Updated: 2025/01/14 18:20:27 by marvin           ###   ########.fr       */
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
	if (fields->wordcount == 7 && parse_material(material, &fields->array[5],
			minirt, curr_line))
		return ;
}

bool	parse_cube(t_minirt *minirt, const t_split *fields, int curr_line)
{
	t_object	*cu;

	if (minirt->scene.num_shapes == SHAPES_MAX)
		return (destroy_2d_arr(fields->array),
			parse_warn_msg(ER_MAX_SHAPES, NULL, curr_line, true), true);
	cu = &minirt->scene.shapes[minirt->scene.num_shapes++];
	if (fields->wordcount < 5 || fields->wordcount > 7)
		return (parse_err_msg(ER_OBJ_FORMAT, ER_EXPECT_TYPE_CU ER_ECU,
				curr_line), destroy_2d_arr(fields->array), false);
	cu->type = CUBIC;
	if (!parse_vec4p(&cu->trans, fields->array[1], minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	if (!parse_vec4v(&cu->orientation, fields->array[2], minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	is_normalised(&cu->orientation, curr_line);
	cu->specs.side_length = ft_atof(fields->array[3], minirt);
	if (!parse_color(&cu->material.color, fields->array[4], curr_line))
		return (destroy_2d_arr(fields->array), false);
	material_init(&cu->material, fields, minirt, curr_line);
	cu->scale = vec4s_re(1, 1, 1, 1);
	cu->rot = rt_extract_rot_vertical(cu->orientation);
	cu->inv_transform = get_inv_tranform_mat4s(cu->rot,
			cu->scale, cu->trans);
	return (destroy_2d_arr(fields->array), true);
}
