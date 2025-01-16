/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:20:32 by nth          #+#    #+#             */
/*   Updated: 2025/01/14 18:20:59 by marvin           ###   ########.fr       */
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

void	get_sphere_extras(t_object *sp)
{
	sp->scale = vec4s_re(sp->radius, sp->radius, sp->radius, sp->radius);
	sp->scale.w = 1.f;
	sp->rot = ini_indentity_mat4s();
	sp->inv_transform = get_inv_tranform_mat4s(sp->rot,
			sp->scale, sp->trans);
}

bool	parse_sphere(t_minirt *minirt, const t_split *fields, int curr_line)
{
	t_object	*sp;

	if (minirt->scene.num_shapes == SHAPES_MAX)
		return (destroy_2d_arr(fields->array),
			parse_warn_msg(ER_MAX_SHAPES, NULL, curr_line, true), true);
	sp = &minirt->scene.shapes[minirt->scene.num_shapes++];
	if (fields->wordcount < 4 || fields->wordcount > 6)
		return (parse_err_msg(ER_OBJ_FORMAT, ER_E_TYPE_SP,
				curr_line), destroy_2d_arr(fields->array), false);
	sp->type = SPHERE;
	if (!parse_vec4p(&sp->trans, fields->array[1], minirt, curr_line))
		return (destroy_2d_arr(fields->array), false);
	sp->radius = ft_atof(fields->array[2], minirt) / 2.0f;
	if (minirt->error_code == 2)
		return (parse_err_msg(ER_OBJ_VALUE, ER_EXPECT_FLOAT, curr_line),
			destroy_2d_arr(fields->array), false);
	if (!parse_color(&sp->material.color, fields->array[3], curr_line))
		return (destroy_2d_arr(fields->array), false);
	material_init(&sp->material, fields, minirt, curr_line);
	get_sphere_extras(sp);
	transpose_mat4s(&sp->inv_transform, &sp->transposed_inverse);
	return (destroy_2d_arr(fields->array), true);
}
