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

#include "minirt.h"
#include "macros.h"
#include "colors.h"
#include <assert.h>

bool	parse_cylinder(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_object	*cylinder;
	float		height;
	t_point		t;

	(*i) += 2;
	cylinder = minirt->scene.shapes + idx;
	cylinder->type = CYLINDER;
	t = parse_point(data, i);
	cylinder->trans = t;
	cylinder->translate = translation_mat(t.x, t.y, t.z);
	cylinder->orientation = parse_vector(data, i);
	is_normalised(&cylinder->orientation, *i, minirt);
	cylinder->radius = parse_float(data, i) / 2;
	height = parse_float(data, i);
	cylinder->specs.min_y = -height / 2;
	cylinder->specs.max_y = height / 2;
	cylinder->specs.closed = true;
	cylinder->material.color = parse_color(data, i, minirt);
	set_material(&cylinder->material, data, i, minirt);
	cylinder->scale_v = create_vec4d(cylinder->radius, height / 2, \
		cylinder->radius);
	cylinder->scale_v.p = 1.f;
	cylinder->scale = scaling_mat(cylinder->radius, height / 2, \
		cylinder->radius);
	cylinder->rot = rt_extract_rot_vertical(cylinder->orientation);
	cylinder->inv_transform = mult_n_mat4d(3, &cylinder->rot, \
		&cylinder->scale, &cylinder->translate);
	cylinder->inv_transform = inverse_mat4d(&cylinder->inv_transform);
	cylinder->transposed_inverse = transpose_mat4d(&cylinder->inv_transform);
	return (true);
}
