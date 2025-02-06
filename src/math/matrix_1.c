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

	m.matrix[0] = v1.x;
	m.matrix[1] = v1.y;
	m.matrix[2] = v1.z;
	m.matrix[3] = v1.p;
	m.matrix[4] = v2.x;
	m.matrix[5] = v2.y;
	m.matrix[6] = v2.z;
	m.matrix[7] = v2.p;
	m.matrix[8] = v3.x;
	m.matrix[9] = v3.y;
	m.matrix[10] = v3.z;
	m.matrix[11] = v3.p;
	m.matrix[12] = v4.x;
	m.matrix[13] = v4.y;
	m.matrix[14] = v4.z;
	m.matrix[15] = v4.p;

	return (m);
}

/*
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
*/
