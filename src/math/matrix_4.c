/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:32:39 by chon              #+#    #+#             */
/*   Updated: 2024/12/16 13:32:39 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_math.h"

float determinant_mat2d(const t_mat2d *m)
{
	return (m->matrix[0] * m->matrix[3] - m->matrix[1] * m->matrix[2]);
}

float determinant_mat3d(t_mat3d m)
{
	return (m.matrix[0] * cofactor_mat3d(&m, 0, 0)
		+ m.matrix[1] * cofactor_mat3d(&m, 0, 1)
		+ m.matrix[2] * cofactor_mat3d(&m, 0, 2));
}

float determinant_mat4d(const t_mat4d *m)
{
	return (m->matrix[0] * determinant_mat3d(submatrix_mat4d(m, 0, 0))
		- m->matrix[1] * determinant_mat3d(submatrix_mat4d(m, 0, 1))
		+ m->matrix[2] * determinant_mat3d(submatrix_mat4d(m, 0, 2))
		- m->matrix[3] * determinant_mat3d(submatrix_mat4d(m, 0, 3)));
}

t_mat4d inverse_mat4d(const t_mat4d *m)
{
	float det;
	t_mat4d new_m;
	int i;
	int row;
	int col;

	det = determinant_mat4d(m);
	i = -1;
	if (!det)
		while (++i < 16)
			new_m.matrix[i] = NAN;
	else
	{
		while (++i < 16)
		{
			col = i / 4;
			row = i % 4;
			new_m.matrix[i] = determinant_mat3d(submatrix_mat4d(m, row, col));
			if (((row + col) % 2))
				new_m.matrix[i] *= -1;
			new_m.matrix[i] /= det;
		}
	}
	return (new_m);
}
