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

#include "minirt_math.h"

t_mat4d	mult_n_mat4d(int num_of_matrices, ...)
{
	t_mat4d	new_m;
	t_idx	idx;
	va_list	args;

	va_start(args, num_of_matrices);
	idx.count = -1;
	idx.i = -1;
	idx.j = -1;
	idx.m1 = va_arg(args, t_mat4d *);
	while (++idx.count < num_of_matrices - 1)
	{
		idx.m2 = va_arg(args, t_mat4d *);
		while (++idx.i < 4)
		{
			while (++idx.j < 4)
				new_m.matrix[idx.i * 4 + idx.j] = \
					dot_values(row(idx.m2, idx.i), col(idx.m1, idx.j));
			idx.j = -1;
		}
		idx.i = -1;
		idx.m1 = &new_m;
	}
	va_end(args);
	return (new_m);
}

t_vec4d	mult_mat4d_vec4d(const t_mat4d *m, const t_vec4d *v)
{
	t_vec4d	new_v;

	new_v.x = m->matrix[0] * v->x + m->matrix[1] * v->y + \
		m->matrix[2] * v->z + m->matrix[3] * v->p;
	new_v.y = m->matrix[4] * v->x + m->matrix[5] * v->y + \
		m->matrix[6] * v->z + m->matrix[7] * v->p;
	new_v.z = m->matrix[8] * v->x + m->matrix[9] * v->y + \
		m->matrix[10] * v->z + m->matrix[11] * v->p;
	new_v.p = m->matrix[12] * v->x + m->matrix[13] * v->y + \
		m->matrix[14] * v->z + m->matrix[15] * v->p;
	return (new_v);
}

t_mat4d	transpose_mat4d(const t_mat4d *m)
{
	t_mat4d	transposed;

	transposed.matrix[0] = m->matrix[0];
	transposed.matrix[1] = m->matrix[4];
	transposed.matrix[2] = m->matrix[8];
	transposed.matrix[3] = m->matrix[12];
	transposed.matrix[4] = m->matrix[1];
	transposed.matrix[5] = m->matrix[5];
	transposed.matrix[6] = m->matrix[9];
	transposed.matrix[7] = m->matrix[13];
	transposed.matrix[8] = m->matrix[2];
	transposed.matrix[9] = m->matrix[6];
	transposed.matrix[10] = m->matrix[10];
	transposed.matrix[11] = m->matrix[14];
	transposed.matrix[12] = m->matrix[3];
	transposed.matrix[13] = m->matrix[7];
	transposed.matrix[14] = m->matrix[11];
	transposed.matrix[15] = m->matrix[15];
	return (transposed);
}
