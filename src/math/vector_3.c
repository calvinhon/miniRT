/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:54:41 by chon              #+#    #+#             */
/*   Updated: 2024/12/11 15:54:41 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_math.h"

t_vec4d	cross_pointers(const t_vec4d *v1, const t_vec4d *v2)
{
	t_vec4d	result;

	result.x = v1->y * v2->z - v1->z * v2->y;
	result.y = v1->z * v2->x - v1->x * v2->z;
	result.z = v1->x * v2->y - v1->y * v2->x;
	result.p = 0.0f;
	return (result);
}

t_vec4d	cross_values(t_vec4d v1, t_vec4d v2)
{
	t_vec4d	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	result.p = 0.0f;
	return (result);
}

t_vec4d	add_vectors(const t_vec4d *v1, const t_vec4d *v2)
{
	t_vec4d	result;

	result.x = v1->x + v2->x;
	result.y = v1->y + v2->y;
	result.z = v1->z + v2->z;
	result.p = v1->p + v2->p;
	return (result);
}

t_vec4d	subtract_points(t_point *p1, t_point *p2)
{
	t_vec4d	result;

	result.x = p1->x - p2->x;
	result.y = p1->y - p2->y;
	result.z = p1->z - p2->z;
	result.p = 0.0f;
	return (result);
}

t_vec4d	subtract_vectors(const t_vec4d *v1, const t_vec4d *v2)
{
	t_vec4d	result;

	result.x = v1->x - v2->x;
	result.y = v1->y - v2->y;
	result.z = v1->z - v2->z;
	result.p = v1->p - v2->p;
	return (result);
}
