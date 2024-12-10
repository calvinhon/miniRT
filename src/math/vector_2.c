#include "minirt_math.h"

double	magnitude(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	normalize(t_vector v)
{
	double		mag_v;

	mag_v = magnitude(v);
	return (create_vector(v.x / mag_v, v.y / mag_v, v.z / mag_v));
}

double	dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	cross(t_vector v1, t_vector v2)
{
	return (create_vector(v1.x * v2.y - v1.y * v2. x,
		v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z));
}
