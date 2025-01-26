/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:35:51 by chon              #+#    #+#             */
/*   Updated: 2025/01/20 10:35:51 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_math.h"

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

t_mat4d	mult_n_mat4d(int num_of_matrices, ...)
{
	t_mat4d	new_m;
	t_idx	idx;
	va_list	args;

	va_start(args, num_of_matrices);
	idx.count = -1;
	idx.i = -1;
	idx.j = -1;
	idx.m1 = va_arg(args, t_mat4d);
	while (++idx.count < num_of_matrices - 1)
	{
		idx.m2 = va_arg(args, t_mat4d);
		while (++idx.i < 4)
		{
			while (++idx.j < 4)
				new_m.matrix[idx.i * 4 + idx.j] =
					dot(row(idx.m2, idx.i), col(idx.m1, idx.j));
			idx.j = -1;
		}
		idx.i = -1;
		idx.m1 = new_m;
	}
	va_end(args);
	return (new_m);
}

t_vec4d	mult_mat4d_vec4d(t_mat4d m, t_vec4d v)
{
	t_vec4d	new_v;

	new_v.x = dot(row(m, 0), v);
	new_v.y = dot(row(m, 1), v);
	new_v.z = dot(row(m, 2), v);
	new_v.p = dot(row(m, 3), v);
	return (new_v);
}

t_mat4d	transpose_mat4d(t_mat4d m)
{
	t_mat4d new_m;
	t_vec4d	v1;
	t_vec4d	v2;
	t_vec4d	v3;
	t_vec4d	v4;

	v1 = col(m, 0);
	v2 = col(m, 1);
	v3 = col(m, 2);
	v4 = col(m, 3);
	new_m = create_mat4d(v1, v2, v3, v4);
	return (new_m);
}
