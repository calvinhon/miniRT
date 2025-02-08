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

#include "minirt.h"
#include "macros.h"
#include "colors.h"

bool	parse_cone(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_object	*cone;
	float		height;

	(*i) += 2;
	cone = minirt->scene.shapes + idx;
	cone->type = CONE;
	cone->trans = parse_point(data, i);
	cone->orientation = parse_vector(data, i);
	is_normalised(&cone->orientation, *i, minirt);
	cone->radius = parse_float(data, i) / 2.0f;
	cone->specs.min_y = parse_float(data, i);
	cone->specs.max_y = parse_float(data, i);
	height = (cone->specs.max_y - cone->specs.min_y) / 2;
	cone->specs.closed = false;
	cone->material.color = parse_color(data, i, minirt);
	set_material(&cone->material, data, i, minirt);
	cone->scale_v = create_vec4d(cone->radius, height, cone->radius);
	cone->scale_v.p = 1.f;
	cone->scale = scaling_mat(cone->radius, height, cone->radius);
	cone->rot = rt_extract_rot_vertical(cone->orientation);
	cone->inv_transform = get_inv_tranform_mat4d(cone->rot,
			cone->scale_v, cone->trans);
	cone->specs.min_y = cone->specs.min_y / height;
	cone->specs.max_y = cone->specs.max_y / height;
	return (true);
}
