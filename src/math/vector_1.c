/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:54:37 by chon              #+#    #+#             */
/*   Updated: 2024/12/11 15:54:37 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_math.h"

t_vec4d	create_vec4d(float x, float y, float z)
{
	t_vec4d	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.p = 0;
	return (v);
}
float	magnitude(const t_vec4d *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
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
