/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:54:41 by chon              #+#    #+#             */
/*   Updated: 2024/12/11 15:54:41 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_math.h"

void	scale_vector(t_vec4d *out, const t_vec4d *v, float factor)
{
	out->x = v->x * factor;
	out->y = v->y * factor;
	out->z = v->z * factor;
	out->p = v->p * factor;
}

t_vec4d	scale_vector_re(const t_vec4d *v, float factor)
{
	return (create_vec4d(v->x * factor, v->y * factor, v->z * factor));
}

t_vec4d	negate_vector(const t_vec4d *v)
{
	t_vec4d	out;

	out.x = -v->x;
	out.y = -v->y;
	out.z = -v->z;
	out.p = -v->p;
	return (out);
}
