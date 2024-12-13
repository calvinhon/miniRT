#include "minirt_math.h"

bool	is_equal_mat4d(t_mat4d m1, t_mat4d m2)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (m1.matrix[i] != m2.matrix[i])
			return (0);
		i++;
	}
	return (1);
}

t_mat4d	mult_2x_mat4d(t_mat4d m1, t_mat4d m2)
{
	t_mat4d	new_m;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = -1;
	while (++j < 4)
	{
		while (++k < 4)
			new_m.matrix[++i] = dot(row(m1, j), col(m2, k));
		k = -1;
	}
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
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++i < 4)
	{
		while (++j < 4)
			new_m.matrix[i] = m.matrix[i];
		j = -1;
	}
	return (new_m);
}
