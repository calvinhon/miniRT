/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 17:55:53 by chon              #+#    #+#             */
/*   Updated: 2025/01/30 17:55:53 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	swap(float *t)
{
	if (t[0] > t[1])
	{
		t[2] = t[0];
		t[0] = t[1];
		t[1] = t[2];
	}
}

t_itx_grp local_intersect(t_scene *s, t_ray *r)
{
	t_itx_grp xs;
	int i;

	i = -1;
	xs.count = 0;
	while (++i < s->num_shapes)
	{
		if (s->shapes[i].type == SPHERE && xs.count + 2 <= MAX_ITX)
			intersect_sphere(r, &s->shapes[i], &xs);
		else if (s->shapes[i].type == PLANE && xs.count + 1 <= MAX_ITX)
			intersect_plane(r, &s->shapes[i], &xs);
		else if (s->shapes[i].type == CYLINDER && xs.count + 2 <= MAX_ITX)
			intersect_cylinder(r, &s->shapes[i], &xs);
		else if (s->shapes[i].type == CUBE && xs.count + 2 <= MAX_ITX)
			intersect_cube(r, &s->shapes[i], &xs);
		// else if (s->shapes[i].type == CONE)
		// 	intersect_cone(r, &s->shapes[i], &xs);
	}
	return (xs);
}
