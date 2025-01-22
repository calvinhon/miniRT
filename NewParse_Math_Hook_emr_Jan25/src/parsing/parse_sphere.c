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

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool	parse_sphere(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_object	*sphere;

	(*i) += 2;
	sphere = minirt->scene.shapes + idx;
	sphere->type = SPHERE;
	sphere->trans = parse_point(data, i);
	sphere->radius = parse_float(data, i) / 2.f;
	sphere->material.color = parse_color(data, i);
	set_material(&sphere->material, data, i, minirt);
	sphere->scale = vec4s_re(sphere->radius, sphere->radius, sphere->radius, 1.f);
	sphere->rot = ini_indentity_mat4s();
	sphere->inv_transform = get_inv_tranform_mat4s(sphere->rot, sphere->scale, sphere->trans);
	transpose_mat4s(&sphere->inv_transform, &sphere->transposed_inverse);
/*

	// test
	printf("shape[%ld], type = %d\n", idx, sphere->type);// test
	//test
	printf("sphere position = %f, %f, %f\n", (minirt->scene.shapes + idx)->trans.x, \
		(minirt->scene.shapes + idx)->trans.y, (minirt->scene.shapes + idx)->trans.z);
	// test
	printf("sphere radius =  %f\n", (minirt->scene.shapes + idx)->radius);
	//test	
	printf("sphere color = %f, %f, %f\n", (minirt->scene.shapes + idx)->material.color.r, \
		(minirt->scene.shapes + idx)->material.color.g, (minirt->scene.shapes + idx)->material.color.b);

*/

	return (true);
}

