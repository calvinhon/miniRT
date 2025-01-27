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
	height = parse_float(data, i);
	cone->specs.min = -height / 2.0f;
	cone->specs.max = height / 2.0f;
	cone->specs.closed = false;
	cone->material.color = parse_color(data, i, minirt);
	set_material(&cone->material, data, i, minirt);
	cone->scale = vec4s_re(cone->radius, height, cone->radius, 1);
	cone->rot = rt_extract_rot_vertical(cone->orientation);
	cone->inv_transform = get_inv_tranform_mat4s(cone->rot,
			cone->scale, cone->trans);
	return (true);
}
