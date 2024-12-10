#include "minirt_math.h"

t_vector	create_vector(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.p = 0;
	return (v);
}

t_vector	add_vectors(t_vector v1, t_vector v2)
{
	return (create_vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vector	subtract_points(t_point p1, t_point p2)
{
	return (create_vector(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z));
}

t_vector	scale_vector(t_vector v, double factor)
{
	return (create_vector(v.x * factor, v.y * factor, v.z * factor));
}

t_vector negate_vector(t_vector v)
{
	return (scale_vector(v, -1));
}
