/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:34:49 by nth          #+#    #+#             */
/*   Updated: 2025/01/14 18:20:16 by marvin           ###   ########.fr       */
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
    t_vec4s color_vec;

    color_vec = material->color.v;
    material->xordc = (t_color)
	{
        .v.a[0] = (int)color_vec.a[0] ^ 1,
        .v.a[1] = (int)color_vec.a[1] ^ 1,
        .v.a[2] = (int)color_vec.a[2] ^ 1,
        .v.a[3] = (int)color_vec.a[3] ^ (OS_MACOS == 0)
    };
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

bool	get_cone_extras(t_object *co, t_minirt *minirt,
		const t_split *fields, int curr_line)
{
	float	height;

	co->radius = ft_atof(fields->array[3], minirt) / 2.0f;
	if (minirt->error_code == 2)
		return (parse_err_msg(ER_OBJ_VALUE, ER_EXPECT_FLOAT, curr_line),
			destroy_2d_arr(fields->array), false);
	height = ft_atof(fields->array[4], minirt);
	if (minirt->error_code == 2)
		return (parse_err_msg(ER_OBJ_VALUE, ER_EXPECT_FLOAT, curr_line),
			destroy_2d_arr(fields->array), false);
	co->specs.min = -height / 2.0f;
	co->specs.max = height / 2.0f;
	co->specs.closed = false;
	if (!parse_color(&co->material.color, fields->array[5], curr_line))
		return (destroy_2d_arr(fields->array), false);
	material_init(&co->material, fields, minirt, curr_line);
	co->scale = vec4s_re(co->radius, height, co->radius, 1);
	co->rot = rt_extract_rot_vertical(co->orientation);
	co->inv_transform = get_inv_tranform_mat4s(co->rot,
			co->scale, co->trans);
	return (true);
}

bool	parse_cone(t_minirt *minirt, const t_split *fields, int curr_line)
{
	t_object	*co;

	if (minirt->scene.num_shapes == SHAPES_MAX)
		return (destroy_2d_arr(fields->array),
			parse_warn_msg(ER_MAX_SHAPES, NULL, curr_line, true), true);
	co = &minirt->scene.shapes[minirt->scene.num_shapes++];
	if (fields->wordcount < 6 || fields->wordcount > 8)
		return (parse_err_msg(ER_OBJ_FORMAT, ER_EXPECT_TYPE_CO ER_ECO,
				curr_line), destroy_2d_arr(fields->array), false);
	co->type = CONE;
	if (!parse_vec4p(&co->trans, fields->array[1], minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	if (!parse_vec4v(&co->orientation, fields->array[2], minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	is_normalised(&co->orientation, curr_line);
	if (!get_cone_extras(co, minirt, fields, curr_line))
		return (false);
	return (destroy_2d_arr(fields->array), true);
}
