/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:50:33 by chon              #+#    #+#             */
/*   Updated: 2025/01/20 16:50:33 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	position(t_ray *r, float t)
{
	t_vec4d	scaled_v;

	scale_vector(&scaled_v, &r->direction, t);
	return (add_v_to_p(&r->origin, &scaled_v));
}

t_ray	create_ray(t_point *origin, t_vec4d *direction)
{
	t_ray	r;

	r.origin = *origin;
	r.direction = *direction;
	return (r);
}

void	transform_ray(t_ray *r, t_mat4d *m)
{
	r->origin = mult_mat4d_pt4d(m, &r->origin);
	r->direction = mult_mat4d_vec4d(m, &r->direction);
}
