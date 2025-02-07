/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:08:31 by nth          #+#    #+#             */
/*   Updated: 2025/01/14 18:20:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "macros.h"
#include "colors.h"

bool	parse_plane(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_object	*plane;
	t_point		t;

	(*i) += 2;
	plane = minirt->scene.shapes + idx;
	plane->type = PLANE;
	t = parse_point(data, i);
	plane->trans = t;
	plane->translate = translation_mat(t.x, t.y, t.z);
	plane->orientation = parse_vector(data, i);
	is_normalised(&plane->orientation, *i, minirt);
	plane->material.color = parse_color(data, i, minirt);
	set_material(&plane->material, data, i, minirt);
	plane->scale_v = create_vec4d(1.f, 1.f, 1.f);
	plane->scale_v.p = 1.f;
	plane->scale = scaling_mat(1.f, 1.f, 1.f);
	plane->rot = rt_extract_rot_vertical(plane->orientation);
	plane->inv_transform = get_inv_tranform_mat4d(plane->rot, \
		plane->scale_v, plane->trans);
	return (plane->center.p = 1.f, true);
}
