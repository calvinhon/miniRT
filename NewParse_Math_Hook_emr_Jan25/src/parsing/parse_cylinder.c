///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   parse_cylinder.c                                   :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:38:59 by nth          #+#    #+#             */
/*   Updated: 2025/01/14 18:20:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
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
	is_normalised(&cylinder->orientation, *i);
	cylinder->radius = parse_float(data, i) / 2.f;
	height = parse_float(data, i);
	cylinder->specs.min = -height / 2.0f;
	cylinder->specs.max = height / 2.0f;
	cylinder->specs.closed = true;
	cylinder->material.color = parse_color(data, i);
	set_material(&cylinder->material, data, i, minirt);
	cylinder->scale = vec4s_re(cylinder->radius, height / 2.f, cylinder->radius, 1);
	cylinder->rot = rt_extract_rot_vertical(cylinder->orientation);
	cylinder->inv_transform = get_inv_tranform_mat4s(cylinder->rot,
			cylinder->scale, cylinder->trans);
	transpose_mat4s(&cylinder->inv_transform, &cylinder->transposed_inverse);
/*
	//test
	printf("shape[%ld], type = %d\n", idx, cylinder->type);// test
	//test
	printf("cylinder position = %f, %f, %f\n", (minirt->scene.shapes + idx)->trans.x, \
		(minirt->scene.shapes + idx)->trans.y, (minirt->scene.shapes + idx)->trans.z);
	// test
	printf("cylinder orientation = %f, %f, %f\n", (minirt->scene.shapes + idx)->orientation.x, \
		(minirt->scene.shapes + idx)->orientation.y, (minirt->scene.shapes + idx)->orientation.z);
	//test
	printf("cylinder radius = %f\n", (minirt->scene.shapes + idx)->radius);
	// test
	printf("cylinder height = %f\n", 2 * cylinder->specs.max );
	
	//test	
	printf("cylinder color = %f, %f, %f\n", (minirt->scene.shapes + idx)->material.color.r, \
		(minirt->scene.shapes + idx)->material.color.g, (minirt->scene.shapes + idx)->material.color.b);
		//test
	printf("Bonus = %c\n", data[*i]);
*/
	return (true);
}
