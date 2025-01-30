/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:37:44 by chon              #+#    #+#             */
/*   Updated: 2025/01/30 18:22:56 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_vec4d cube_normal_at(t_object *o, t_point *wrld_p)

void	check_axis(float *axis, float origin, float direction)
{
	float	tmin_numerator;
	float	tmax_numerator;

	tmin_numerator = -1 - origin;
	tmax_numerator = 1 - origin;
	if (fabsf(direction) >= EPSILON)
	{
		axis[0] = tmin_numerator / direction;
		axis[1] = tmax_numerator / direction;
	}
	else
	{
		axis[0] = tmin_numerator * INFINITY;
		axis[1] = tmax_numerator * INFINITY;
	}
	swap(axis);
}

void intersect_cube(t_ray *r, t_object *o, t_itx_grp *xs)
{
	t_ray	trfm_r;
	float	x[3];
	float	y[3];
	float	z[3];

	trfm_r = *r;
	transform_ray(&trfm_r, &o->inv_transform);
	check_axis(x, trfm_r.origin.x, trfm_r.direction.x);
	check_axis(y, trfm_r.origin.y, trfm_r.direction.y);
	check_axis(z, trfm_r.origin.z, trfm_r.direction.z);
	x[2] = fmax(x[0], fmax(y[0], z[0]));
	y[2] = fmin(x[1], fmin(y[1], z[1]));
	if (x[2] > y[2])
		return ;
	xs->arr[xs->count].obj = o;
	xs->arr[xs->count++].t = fmax(x[0], fmax(y[0], z[0]));
	xs->arr[xs->count].obj = o;
	xs->arr[xs->count++].t = fmin(x[1], fmin(y[1], z[1]));
}
