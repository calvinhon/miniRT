#include "minirt_math.h"

double	determinant_mat2d(t_mat2d m)
{
	return (m.matrix[0] * m.matrix[3] - m.matrix[1] * m.matrix[2]);
}

double	determinant_mat3d(t_mat3d m)
{
	return (m.matrix[0] * cofactor_mat3d(m, 0, 0) +
		m.matrix[1] * cofactor_mat3d(m, 0, 1) +
		m.matrix[2] * cofactor_mat3d(m, 0, 2));
}

double	determinant_mat4d(t_mat4d m)
{
	return (m.matrix[0] * cofactor_mat3d(submatrix_mat4d(m, 0, 0)
}
