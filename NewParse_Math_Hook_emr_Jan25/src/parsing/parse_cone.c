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

//static void	set_material_1(t_material *material, char *data, size_t *i, t_minirt *minirt)
//{
//    t_vec4s color_vec;

//    color_vec = material->color.v;
//    material->xordc = (t_color)
//	{
//        .v.a[0] = (int)color_vec.a[0] ^ 1,
//        .v.a[1] = (int)color_vec.a[1] ^ 1,
//        .v.a[2] = (int)color_vec.a[2] ^ 1,
//        .v.a[3] = (int)color_vec.a[3] ^ (OS_MACOS == 0)
//    };
//	material->ambient = 0.1;
//	material->diffuse = 0.9;
//	material->specular = 0.9;
//	material->sheen = 200;
//	material->reflective = 0.0;
//	material->transparency = 0.0;
//	material->refractive_index = 1.0;
//	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == ',')
//		(*i)++;
//	//test
//	printf("data[%ld] = %c\n", *i, data[*i]);

//	if (data[*i] == 'M')
//	{
//		(*i)++;
//		parse_material(material, data, i, minirt);
//	}
//}

bool	parse_cone(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_object	*cone;
	float		height;

	(*i) += 2;
	cone = minirt->scene.shapes + idx;
	cone->type = CONE;
	cone->trans = parse_point(data, i);
	cone->orientation = parse_vector(data, i);
	is_normalised(&cone->orientation, *i);
	cone->radius = parse_float(data, i)/2.0f;
	height = parse_float(data, i);
	cone->specs.min = -height / 2.0f;
	cone->specs.max = height / 2.0f;
	cone->specs.closed = false;
	cone->material.color = parse_color(data, i);
	set_material(&cone->material, data, i, minirt);
	cone->scale = vec4s_re(cone->radius, height, cone->radius, 1);
	cone->rot = rt_extract_rot_vertical(cone->orientation);
	cone->inv_transform = get_inv_tranform_mat4s(cone->rot,
			cone->scale, cone->trans);
	/*
		// test
	printf("shape[%ld], type = %d\n", idx, cone->type);// test
	//test
	printf("cone position = %f, %f, %f\n", (minirt->scene.shapes + idx)->trans.x, \
		(minirt->scene.shapes + idx)->trans.y, (minirt->scene.shapes + idx)->trans.z);
	// test
	printf("cone radius =  %f\n", (minirt->scene.shapes + idx)->radius);
	//test	
	printf("cone color = %f, %f, %f\n", (minirt->scene.shapes + idx)->material.color.r, \
		(minirt->scene.shapes + idx)->material.color.g, (minirt->scene.shapes + idx)->material.color.b);
	*/
return (true);
}
