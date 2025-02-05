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

#include "minirt.h"
#include "macros.h"
#include "colors.h"

bool parse_sphere(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_object *sphere;
	t_point t;

	(*i) += 2;
	sphere = minirt->scene.shapes + idx;
	sphere->type = SPHERE;
	t = parse_point(data, i);
	// sphere->trans = t;
	sphere->translate = translation_mat(t.x, t.y, t.z);
	sphere->radius = parse_float(data, i) / 2.f;
	sphere->material.color = parse_color(data, i, minirt);
	set_material(&sphere->material, data, i, minirt);
	sphere->scale = scaling_mat(sphere->radius, sphere->radius, sphere->radius);
	sphere->rot = identity_mat();
	sphere->inv_transform = mult_n_mat4d(3, &sphere->rot, &sphere->scale,
										 &sphere->translate);
	sphere->inv_transform = inverse_mat4d(&sphere->inv_transform);
	return (true);
}
