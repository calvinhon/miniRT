#include "minirt_math.h"

t_mat4d	rotate_mat_x(double rad)
{
	t_mat4d	m;
	int		i;

	i = -1;
	while (++i < 16)
	{
		if (i == 0 || i == 15)
			m.matrix[i] = 1;
		else if (i == 5 || i == 10)
			m.matrix[i] = cos(rad);
		else if (i == 6)
			m.matrix[i] = -sin(rad);
		else if (i == 9)
			m.matrix[i] = sin(rad);
		else
			m.matrix[i] = 0;
	}
	return (m);
}

t_mat4d	rotate_mat_y(double rad)
{
	t_mat4d	m;
	int		i;

	i = -1;
	while (++i < 16)
	{
		if (i == 0 || i == 10)
			m.matrix[i] = cos(rad);
		else if (i == 5 || i == 15)
			m.matrix[i] = 1;
		else if (i == 2)
			m.matrix[i] = sin(rad);
		else if (i == 8)
			m.matrix[i] = -sin(rad);
		else
			m.matrix[i] = 0;
	}
	return (m);
}

t_mat4d	rotate_mat_z(double rad)
{
	t_mat4d	m;
	int		i;

	i = -1;
	while (++i < 16)
	{
		if (i == 10 || i == 15)
			m.matrix[i] = 1;
		else if (i == 0 || i == 5)
			m.matrix[i] = cos(rad);
		else if (i == 1)
			m.matrix[i] = -sin(rad);
		else if (i == 4)
			m.matrix[i] = sin(rad);
		else
			m.matrix[i] = 0;
	}
	return (m);
}

t_mat4d	shear_mat(t_shear s)
{
	t_mat4d	m;
	int		i;

	i = -1;
	while (++i < 16)
	{
		if (i == 0 || i == 5 || i == 10 || i == 15)
			m.matrix[i] = 1;
		else if (i == 1)
			m.matrix[i] = s.x_y;
		else if (i == 2)
			m.matrix[i] = s.x_z;
		else if (i == 4)
			m.matrix[i] = s.y_x;
		else if (i == 6)
			m.matrix[i] = s.y_z;
		else if (i == 8)
			m.matrix[i] = s.z_x;
		else if (i == 9)
			m.matrix[i] = s.z_y;
		else
			m.matrix[i] = 0;
	}
	return (m);
}
