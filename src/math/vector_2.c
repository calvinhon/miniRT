#include "minirt_math.h"

double	magnitude(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	normalize(t_vector v)
{
	t_vector	new_v;
	double		mag_v;

	mag_v = magnitude(v);
	new_v.x = v.x / mag_v;
	new_v.y = v.y / mag_v;
	new_v.z = v.z / mag_v;
	return (new_v);
}

double	dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
