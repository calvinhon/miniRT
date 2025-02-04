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
	plane->translate = translation_mat(t.x, t.y, t.z);
	plane->orientation = parse_vector(data, i);
	is_normalised(&plane->orientation, *i, minirt);
	plane->material.color = parse_color(data, i, minirt);
	set_material(&plane->material, data, i, minirt);
	// turn of refractive
	// turn of refractive
	if (plane->material.refractive_index > 0.f)
	{
		ft_printf("Warning: Plane cannot have refractive index\n");
		plane->material.refractive_index = 0.f;
	}
	//
	plane->scale = scaling_mat(1.f, 1.f, 1.f);
	plane->rot = rt_extract_rot_vertical(plane->orientation);
	plane->inv_transform = mult_n_mat4d(3, &plane->rot, &plane->scale, \
		&plane->translate);
	plane->inv_transform = inverse_mat4d(&plane->inv_transform);
	return (plane->center.p = 1.f, true);
}
