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

bool parse_cone(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_object *cone;
	t_point t;

	(*i) += 2;
	cone = minirt->scene.shapes + idx;
	cone->type = CONE;
	t = parse_point(data, i);
	cone->translate = translation_mat(t.x, t.y, t.z);
	cone->orientation = parse_vector(data, i);
	is_normalised(&cone->orientation, *i, minirt);
	cone->radius = parse_float(data, i) / 2.0f;
	cone->specs.min_y = parse_float(data, i);
	cone->specs.max_y = parse_float(data, i);
	cone->specs.closed = true;
	cone->material.color = parse_color(data, i, minirt);
	set_material(&cone->material, data, i, minirt);
	cone->scale = scaling_mat(cone->radius, cone->specs.max_y - cone->specs.min_y, cone->radius);
	cone->rot = rt_extract_rot_vertical(cone->orientation);
	cone->inv_transform = mult_n_mat4d(3,
									   &cone->rot, &cone->scale, &cone->translate);
	cone->inv_transform = inverse_mat4d(&cone->inv_transform);
	return (true);
}
