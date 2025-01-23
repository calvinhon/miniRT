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

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool	parse_plane(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_object	*plane;

	(*i) += 2;
	plane = minirt->scene.shapes + idx;
	plane->type = PLANE;
	plane->trans = parse_point(data, i);
	plane->orientation = parse_vector(data, i);
	is_normalised(&plane->orientation, *i, minirt);
	plane->material.color = parse_color(data, i, minirt);
	set_material(&plane->material, data, i, minirt);
	//
	plane->scale = vec4s_re(1.f, 1.f, 1.f, 1.f);
	plane->rot = rt_extract_rot_vertical(plane->orientation);
	plane->inv_transform = get_inv_tranform_mat4s(plane->rot,
			plane->scale, plane->trans);
	transpose_mat4s(&plane->inv_transform, &plane->transposed_inverse);

/*
	// test
	printf("shape[%ld], type = %d\n", idx, plane->type);// test
	//test
	printf("plane position = %f, %f, %f\n", (minirt->scene.shapes + idx)->trans.x, \
		(minirt->scene.shapes + idx)->trans.y, (minirt->scene.shapes + idx)->trans.z);
	// test
	printf("plane orientation = %f, %f, %f\n", (minirt->scene.shapes + idx)->orientation.x, \
		(minirt->scene.shapes + idx)->orientation.y, (minirt->scene.shapes + idx)->orientation.z);

	//test	
	printf("plane color = %f, %f, %f\n", (minirt->scene.shapes + idx)->material.color.r, \
		(minirt->scene.shapes + idx)->material.color.g, (minirt->scene.shapes + idx)->material.color.b);
	//test
	printf("Bonus = %c\n", data[*i]);
*/
	
	return (plane->center.w = 1.f, true);
}
