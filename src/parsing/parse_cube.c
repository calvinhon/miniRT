/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:38:04 by nth          #+#    #+#             */
/*   Updated: 2025/01/14 18:20:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "macros.h"
// #include "libft.h"
#include "colors.h"

bool parse_cube(t_minirt *minirt, char *data, size_t *i, size_t idx)
{

	t_object *cube;
	t_point t;

	(*i) += 2;
	cube = minirt->scene.shapes + idx;
	cube->type = CUBE;
	t = parse_point(data, i);
	cube->translate = translation_mat(t.x, t.y, t.z);
	cube->orientation = parse_vector(data, i);
	is_normalised(&cube->orientation, *i, minirt);
	cube->specs.side_length = parse_float(data, i);
	cube->material.color = parse_color(data, i, minirt);
	set_material(&cube->material, data, i, minirt);
	// cube->scale = vec4s_re(1.f, 1.f, 1.f, 1.f);
	cube->rot = rt_extract_rot_vertical(cube->orientation);
	cube->inv_transform = mult_n_mat4d(2, &cube->rot, &cube->translate);
	cube->inv_transform = inverse_mat4d(&cube->inv_transform);
	return (true);
}
