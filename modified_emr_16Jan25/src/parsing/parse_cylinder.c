/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:38:59 by nth          #+#    #+#             */
/*   Updated: 2025/01/14 18:20:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"
#include <assert.h>

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
	if (fields->wordcount == 8 && parse_material(material, &fields->array[6],
			minirt, curr_line))
		return ;
}

bool	get_cylinder_extras(t_object *cy, t_minirt *minirt,
		const t_split *fields, int curr_line)
{
	float	height;

	cy->radius = ft_atof(fields->array[3], minirt) / 2.0f;
	if (minirt->error_code == 2)
		return (parse_err_msg(ER_OBJ_VALUE, ER_EXPECT_FLOAT, curr_line),
			destroy_2d_arr(fields->array), false);
	height = ft_atof(fields->array[4], minirt);
	if (minirt->error_code == 2)
		return (parse_err_msg(ER_OBJ_VALUE, ER_EXPECT_FLOAT, curr_line),
			destroy_2d_arr(fields->array), false);
	cy->specs.min = -height / 2.0f;
	cy->specs.max = height / 2.0f;
	cy->specs.closed = true;
	if (!parse_color(&cy->material.color, fields->array[5], curr_line))
		return (destroy_2d_arr(fields->array), false);
	material_init(&cy->material, fields, minirt, curr_line);
	cy->scale = vec4s_re(cy->radius, height / 2.f, cy->radius, 1);
	cy->rot = rt_extract_rot_vertical(cy->orientation);
	cy->inv_transform = get_inv_tranform_mat4s(cy->rot,
			cy->scale, cy->trans);
	transpose_mat4s(&cy->inv_transform, &cy->transposed_inverse);
	return (true);
}

//Radius does not affect the cylinder (Investigate)
bool	parse_cylinder(t_minirt *minirt, const t_split *fields, int curr_line)
{
	t_object	*cy;

	if (minirt->scene.num_shapes == SHAPES_MAX)
		return (destroy_2d_arr(fields->array),
			parse_warn_msg(ER_MAX_SHAPES, NULL, curr_line, true), true);
	cy = &minirt->scene.shapes[minirt->scene.num_shapes++];
	if (fields->wordcount < 6 || fields->wordcount > 8)
		return (parse_err_msg(ER_OBJ_FORMAT, ER_EXPECT_TYPE_CY ER_ECY,
				curr_line), destroy_2d_arr(fields->array), false);
	cy->type = CYLINDER;
	if (!parse_vec4p(&cy->trans, fields->array[1], minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	if (!parse_vec4v(&cy->orientation, fields->array[2], minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	is_normalised(&cy->orientation, curr_line);
	if (!get_cylinder_extras(cy, minirt, fields, curr_line))
		return (false);
	return (destroy_2d_arr(fields->array), true);
}
