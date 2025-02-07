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

	new_v.x = dot_values(row(m, 0), *v);
	new_v.y = dot_values(row(m, 1), *v);
	new_v.z = dot_values(row(m, 2), *v);
	new_v.p = dot_values(row(m, 3), *v);
	return (new_v);
}

t_mat4d	transpose_mat4d(const t_mat4d *m)
{
	return (fill_matrix(col(m, 0), col(m, 1), col(m, 2), col(m, 3)));
}
