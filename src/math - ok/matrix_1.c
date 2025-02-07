/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:19:58 by chon              #+#    #+#             */
/*   Updated: 2025/01/30 13:57:11 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_math.h"

t_vec4d	row(const t_mat4d *m, int i)
{
	t_vec4d	v;

	v.x = m->matrix[i * 4];
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

void	fill_row(t_mat4d *m, int row, t_vec4d v)
{
	m->matrix[row * 4] = v.x;
	m->matrix[row * 4 + 1] = v.y;
	m->matrix[row * 4 + 2] = v.z;
	m->matrix[row * 4 + 3] = v.p;
}

t_mat4d	fill_matrix(t_vec4d v1, t_vec4d v2, t_vec4d v3, t_vec4d v4)
{
	t_mat4d	m;

	fill_row(&m, 0, v1);
	fill_row(&m, 1, v2);
	fill_row(&m, 2, v3);
	fill_row(&m, 3, v4);
	return (m);
}
