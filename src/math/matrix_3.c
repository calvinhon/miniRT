#include "minirt_math.h"

t_mat2d submatrix_mat3d(const t_mat3d *m, int row, int col)
{
	t_mat2d sub_m;
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < 9)
		if (i / 3 != row && i % 3 != col)
			sub_m.matrix[++j] = m->matrix[i];
	return (sub_m);
}

t_mat3d submatrix_mat4d(const t_mat4d *m, int row, int col)
{
	t_mat3d sub_m;
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < 16)
		if (i / 4 != row && i % 4 != col)
			sub_m.matrix[++j] = m->matrix[i];
	return (sub_m);
}

float minor_mat3d(const t_mat3d *m, int row, int col)
{
	t_mat2d m2d;

	m2d = submatrix_mat3d(m, row, col);
	return (determinant_mat2d(&m2d));
}

float cofactor_mat3d(const t_mat3d *m, int row, int col)
{
	if (!((row + col) % 2))
		return (minor_mat3d(m, row, col));
	return (-minor_mat3d(m, row, col));
}
