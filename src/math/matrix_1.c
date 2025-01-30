/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:19:58 by chon              #+#    #+#             */
/*   Updated: 2025/01/30 13:20:44 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_math.h"

t_vec4d	row(const t_mat4d *m, int i)
{
	t_vec4d	v;

	v.x = m->matrix[0 + i * 4];
	v.y = m->matrix[1 + i * 4];
	v.z = m->matrix[2 + i * 4];
	v.p = m->matrix[3 + i * 4];
	return (v);
}

t_vec4d	col(const t_mat4d *m, int i)
{
	t_vec4d	v;

	v.x = m->matrix[i];
	v.y = m->matrix[i + 4];
	v.z = m->matrix[i + 8];
	v.p = m->matrix[i + 12];
	return (v);
}
