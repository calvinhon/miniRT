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

float	magnitude(const t_vec4d *v)
{
	return (sqrtf(v->x * v->x + v->y * v->y + v->z * v->z + v->p * v->p));
}

t_vec4d	normalize(const t_vec4d *v)
{
	t_vec4d	result;
	float	mag_v;

	mag_v = sqrtf(v->x * v->x + v->y * v->y + v->z * v->z + v->p * v->p);
	if (mag_v < EPSILON)
	{
		result.x = 0.f;
		result.y = 0.f;
		result.z = 0.f;
		result.p = 0.f;
	}
	else
	{
		result.x = v->x / mag_v;
		result.y = v->y / mag_v;
		result.z = v->z / mag_v;
		result.p = v->p / mag_v;
	}

	return (result);
}

void	normalize_vec4d(t_vec4d *v)
{
	float	mag_v;

	mag_v = sqrtf(v->x * v->x + v->y * v->y + v->z * v->z + v->p * v->p);
	if (mag_v < EPSILON)
	{
		v->x = 0.f;
		v->y = 0.f;
		v->z = 0.f;
		v->p = 0.f;
	}
	else
	{
		v->x /= mag_v;
		v->y /= mag_v;
		v->z /= mag_v;
		v->p /= mag_v;
	}
}

float	dot_pointers(const t_vec4d *v1, const t_vec4d *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z + v1->p * v2->p);
}

float	dot_values(t_vec4d v1, t_vec4d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.p * v2.p);
}
/*

float	magnitude(const t_vec4d *v)
{
	return (sqrtf(v->x * v->x + v->y * v->y + v->z * v->z));
}

t_vec4d	normalize(const t_vec4d *v)
{
	float	mag_v;

	mag_v = magnitude(v);
	return (create_vec4d(v->x / mag_v, v->y / mag_v, v->z / mag_v));
}

void	normalize_vec4d(t_vec4d *v)
{
	float	mag_v;

	mag_v = magnitude(v);
	if (mag_v < EPSILON)
		*v = create_vec4d(0.f, 0.f, 0.f);
	*v = create_vec4d(v->x / mag_v, v->y / mag_v, v->z / mag_v);
}

float	dot_pointers(const t_vec4d *v1, const t_vec4d *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z + v1->p * v2->p);
}

float	dot_values(t_vec4d v1, t_vec4d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.p * v2.p);
}
*/