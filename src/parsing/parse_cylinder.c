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

	(*i) += 2;
	cylinder = minirt->scene.shapes + idx;
	cylinder->type = CYLINDER;
	cylinder->trans = parse_point(data, i);
	cylinder->orientation = parse_vector(data, i);
	is_normalised(&cylinder->orientation, *i, minirt);
	cylinder->radius = parse_float(data, i) / 2;
	height = parse_float(data, i);
	cylinder->specs.min_y = -height / (2.f * cylinder->radius);
	cylinder->specs.max_y = height / (2.f * cylinder->radius);
	cylinder->specs.closed = true;
	cylinder->material.color = parse_color(data, i, minirt);
	set_material(&cylinder->material, data, i, minirt);
	cylinder->scale_v = create_vec4d(cylinder->radius, cylinder->radius, \
		cylinder->radius);
	cylinder->scale_v.p = 1.f;
	cylinder->rot = rt_extract_rot_vertical(cylinder->orientation);
	cylinder->inv_transform = get_inv_tranform_mat4d(cylinder->rot,
			cylinder->scale_v, cylinder->trans);
	return (true);
}
