#include "minirt_math.h"

t_mat2d	submatrix_mat3d(t_mat3d m, int row, int col)
{
	double	arr[4];
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++i < 9)
		if (i / 3 != row && i % 3 != col)
			arr[++j] = m.matrix[i];
	return (create_mat2d(create_vec2d(arr[0], arr[1]),
		create_vec2d(arr[2], arr[3])));
}

t_mat3d	submatrix_mat4d(t_mat4d m, int row, int col)
{
	double	arr[9];
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++i < 16)
		if (i / 4 != row && i % 4 != col)
			arr[++j] = m.matrix[i];
	return (create_mat3d(create_vec3d(arr[0], arr[1], arr[2]),
		create_vec3d(arr[3], arr[4], arr[5]),
		create_vec3d(arr[6], arr[7], arr[8])));
}

double	minor_mat3d(t_mat3d m, int row, int col)
{
	return (determinant_mat2d(submatrix_mat3d(m, row, col)));
}

double	cofactor_mat3d(t_mat3d m, int row, int col)
{
	if (!((row + col) % 2))
		return (minor_mat3d(m, row, col));
	return (-minor_mat3d(m, row, col));
}
