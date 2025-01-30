/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:54:41 by chon              #+#    #+#             */
/*   Updated: 2024/12/11 15:54:41 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_math.h"

float magnitude(const t_vec4d *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

t_vec4d normalize(const t_vec4d *v)
{
	float mag_v;

	mag_v = magnitude(v);
	return (create_vec4d(v->x / mag_v, v->y / mag_v, v->z / mag_v));
}

float dot_pointers(const t_vec4d *v1, const t_vec4d *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z + v1->p * v2->p);
}

float dot_values(t_vec4d v1, t_vec4d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.p * v2.p);
}

t_vec4d cross_pointers(const t_vec4d *v1, const t_vec4d *v2)
{
	return (create_vec4d(
		v1->y * v2->z - v1->z * v2->y,
		v1->z * v2->x - v1->x * v2->z,
		v1->x * v2->y - v1->y * v2->x));
}

t_vec4d cross_values(t_vec4d v1, t_vec4d v2)
{
	return (create_vec4d(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x));
}
