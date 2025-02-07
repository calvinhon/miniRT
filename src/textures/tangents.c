/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tangents.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:16:37 by nth          #+#    #+#             */
/*   Updated: 2024/11/19 14:46:34 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_vec4d	rt_get_cylinder_tangent(t_vec4d *local_normal, t_object *cylinder)
// {
// 	const t_vec4d	j_hat = create_vec4d(0, 1, 0);
// 	t_vec4d			tangent;

// 	(void)cylinder;
// 	if (fabsf(local_normal->y) < 0.999f)
// 	{
// 		cross_vec4s(&tangent, *local_normal, j_hat);
// 	}
// 	else
// 	{
// 		tangent = create_vec4d(1, 0, 0);
// 	}
// 	normalize(&tangent);
// 	return (tangent);
// }

// t_vec4d	rt_get_sphere_tangent(t_vec4d *local_normal)
// {
// 	t_vec4d			reference;
// 	t_vec4d			retval;

// 	if (fabsf(magnitude(*local_normal)) < 0.999f)
// 		reference = create_vec4d(0, 1, 0);
// 	else
// 		reference = create_vec4d(1, 0, 0);
// 	cross_vec4s(&retval, reference, *local_normal);
// 	normalize(&retval);
// 	return (retval);
// }

// t_vec4d	rt_get_plane_tangent(t_vec4d *local_normal)
// {
// 	t_vec4d	tangent;

// 	if (fabsf(local_normal->y) < 0.999f)
// 		cross_vec4s(&tangent, create_vec4d(0, 1, 0), *local_normal);
// 	else
// 		cross_vec4s(&tangent, create_vec4d(1, 0, 0), *local_normal);
// 	normalize(&tangent);
// 	return (tangent);
// }
