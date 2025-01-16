/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:05:39 by nth          #+#    #+#             */
/*   Updated: 2024/11/19 16:45:03 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec4s	reflect(t_vec4s *in, t_vec4s *normal)
{
	t_vec4s	op;
	t_vec4s	reflect;
	float	dot;

	dot_vec4s(&dot, in, normal);
	op = scale_vec4s_re(*normal, 2.f * dot);
	sub_vec4s(&reflect, in, &op);
	normalize_vec4s(&reflect);
	return (reflect);
}

void	ray_create(t_ray *ray, t_vec4s *origin, t_vec4s *direction)
{
	ray->origin = *origin;
	ray->direction = *direction;
}

void	ray_position(t_vec4s *result, const t_ray *ray, float t)
{
	const t_vec4s	scaled_dir = scale_vec4s_re(ray->direction, t);
	const t_vec4s	sum = add_vec4s_re(ray->origin, scaled_dir);

	*result = vec4s_re(sum.x, sum.y, sum.z, 1.f);
}

void	ray_transform(t_ray *ray, const t_mat4s *matrix)
{
	const t_vec4s	origin = ray->origin;
	const t_vec4s	direction = ray->direction;

	cross_mat4s_vec4s(matrix, &origin, &ray->origin);
	cross_mat4s_vec4s(matrix, &direction, &ray->direction);
}
