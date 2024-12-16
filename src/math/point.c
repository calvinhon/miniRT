/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:10:08 by chon              #+#    #+#             */
/*   Updated: 2024/12/16 15:15:19 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_math.h"

t_point create_point(double x, double y, double z)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = z;
	p.p = 1;
	return (p);
}

t_point add_v_to_p(t_point p, t_vec4d v)
{
	return (create_point(p.x + v.x, p.y + v.y, p.z + v.z));
}

t_point	minus_v_from_p(t_point p, t_vec4d v)
{
	return (create_point(p.x - v.x, p.y - v.y, p.z - v.z));
}

double	dot_v_p(t_vec4d v, t_point p)
{
	return (v.x * p.x + v.y * p.y + v.z * p.z + v.p * p.p);
}

t_point	mult_mat4d_pt4d(t_mat4d m, t_point p)
{
	t_point	new_p;

	new_p.x = dot_v_p(row(m, 0), p);
	new_p.y = dot_v_p(row(m, 1), p);
	new_p.z = dot_v_p(row(m, 2), p);
	new_p.p = dot_v_p(row(m, 3), p);
	return (new_p);
}
