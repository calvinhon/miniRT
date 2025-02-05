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

t_vec4d	add_vectors(const t_vec4d *v1, const t_vec4d *v2)
{
	return (create_vec4d(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z));
}

t_vec4d	subtract_points(t_point *p1, t_point *p2)
{
	return (create_vec4d(p1->x - p2->x, p1->y - p2->y, p1->z - p2->z));
}

t_vec4d	subtract_vectors(const t_vec4d *v1, const t_vec4d *v2)
{
	return (create_vec4d(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z));
}
t_vec4d	subtract_vectors_val(const t_vec4d v1, const t_vec4d v2)
{
	return (create_vec4d(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}
