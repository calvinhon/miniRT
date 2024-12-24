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

t_vec4d	create_vector(double x, double y, double z)
{
	t_vec4d	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.p = 0;
	return (v);
}

t_vec4d	add_vectors(t_vec4d v1, t_vec4d v2)
{
	return (create_vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vec4d	subtract_points(t_point p1, t_point p2)
{
	return (create_vector(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z));
}

t_vec4d	scale_vector(t_vec4d v, double factor)
{
	return (create_vector(v.x * factor, v.y * factor, v.z * factor));
}

t_vec4d	negate_vector(t_vec4d v)
{
	return (scale_vector(v, -1));
}
