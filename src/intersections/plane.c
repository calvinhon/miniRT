/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:57:01 by chon              #+#    #+#             */
/*   Updated: 2025/02/03 16:03:36 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4d	plane_normal_at(t_object *o, t_point *wrld_p)
{
	if (o->material.bump_map)
		return (apply_bump_map(wrld_p, o->material.bump_map, &o->orientation));
	return (o->orientation);
}

void	intersect_plane(t_ray *r, t_object *o, t_itx_grp *xs)
{
	t_ray	trans_r;
	float	t;

	trans_r = *r;
	transform_ray(&trans_r, &o->inv_transform);
	t = (-trans_r.origin.y + EPSILON) / trans_r.direction.y;
	if (xs->count + 1 >= MAX_ITX || fabsf(trans_r.direction.y) < EPSILON)
		return ;
	xs->arr[xs->count].obj = o;
	xs->arr[xs->count++].t = t;
}
