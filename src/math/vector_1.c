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

t_vec4d	create_vec4d(float x, float y, float z)
{
	t_vec4d	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.p = 0;
	return (v);
}

t_vec4d	subtract_vectors_val(const t_vec4d v1, const t_vec4d v2)
{
	return (create_vec4d(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}
