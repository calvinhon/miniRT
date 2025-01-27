/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:38:59 by nth               #+#    #+#             */
/*   Updated: 2025/01/14 18:20:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"
#include <assert.h>

bool	parse_cylinder(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_object	*cylinder;
	float		height;

	(*i) += 2;
	cylinder = minirt->scene.shapes + idx;
	cylinder->type = CYLINDER;
	cylinder->trans = parse_point(data, i);
	cylinder->orientation = parse_vector(data, i);
	is_normalised(&cylinder->orientation, *i, minirt);
	cylinder->radius = parse_float(data, i) / 2.f;
	height = parse_float(data, i);
	cylinder->specs.min = -height / 2.0f;
	cylinder->specs.max = height / 2.0f;
	cylinder->specs.closed = true;
	cylinder->material.color = parse_color(data, i, minirt);
	set_material(&cylinder->material, data, i, minirt);
	cylinder->scale = vec4s_re(cylinder->radius, height / 2.f, \
		cylinder->radius, 1);
	cylinder->rot = rt_extract_rot_vertical(cylinder->orientation);
	cylinder->inv_transform = get_inv_tranform_mat4s(cylinder->rot,
			cylinder->scale, cylinder->trans);
	transpose_mat4s(&cylinder->inv_transform, &cylinder->transposed_inverse);
	return (true);
}
