/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tangents.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:16:37 by nth          #+#    #+#             */
/*   Updated: 2024/11/19 14:46:34 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec4s	rt_get_cylinder_tangent(t_vec4s *local_normal, t_object *cylinder)
{
	const t_vec4s	j_hat = vec4sv_re(0, 1, 0);
	t_vec4s			tangent;

	(void)cylinder;
	if (fabsf(local_normal->y) < 0.999f)
	{
		cross_vec4s(&tangent, *local_normal, j_hat);
	}
	else
	{
		tangent = vec4sv_re(1, 0, 0);
	}
	normalize_vec4s(&tangent);
	return (tangent);
}

t_vec4s	rt_get_sphere_tangent(t_vec4s *local_normal)
{
	t_vec4s			reference;
	t_vec4s			retval;

	if (fabsf(magnitude_vec4s_re(*local_normal)) < 0.999f)
		reference = vec4sv_re(0, 1, 0);
	else
		reference = vec4sv_re(1, 0, 0);
	cross_vec4s(&retval, reference, *local_normal);
	normalize_vec4s(&retval);
	return (retval);
}

t_vec4s	rt_get_plane_tangent(t_vec4s *local_normal)
{
	t_vec4s	tangent;

	if (fabsf(local_normal->y) < 0.999f)
		cross_vec4s(&tangent, vec4sv_re(0, 1, 0), *local_normal);
	else
		cross_vec4s(&tangent, vec4sv_re(1, 0, 0), *local_normal);
	normalize_vec4s(&tangent);
	return (tangent);
}
