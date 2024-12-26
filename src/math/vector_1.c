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

t_vec2d create_vec2d(double x, double y)
{
	t_vec2d v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vec3d create_vec3d(double x, double y, double z)
{
	t_vec3d v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec4d create_vec4d(double x, double y, double z)
{
	t_vec4d	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.p = 0;
	return (v);
}
