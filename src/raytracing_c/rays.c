/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:55:13 by chon              #+#    #+#             */
/*   Updated: 2025/01/13 15:55:13 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	position(t_ray *r, float t)
{
	return (add_v_to_p(r->origin, scale_vector(r->direction, t)));
}

<<<<<<< HEAD
t_ray	create_ray(t_point origin, t_vec4d direction)
=======
t_ray	create_ray(t_point *origin, t_vec4d *direction)
>>>>>>> 81bd0ab25fe8b8f98353709f500febd6c4c4c223
{
	t_ray	r;

	r.origin = *origin;
	r.direction = *direction;
	return (r);
}

void	transform_ray(t_ray *r, t_mat4d *m)
{
	r->origin = mult_mat4d_pt4d(*m, r->origin);
	r->direction = mult_mat4d_vec4d(*m, r->direction);
}