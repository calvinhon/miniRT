#include "minirt_math.h"

t_vector	create_vector(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector	add_vectors(t_vector v1, t_vector v2)
{
	t_vector	new_v;

	new_v.x = v1.x + v2.x;
	new_v.y = v1.y + v2.y;
	new_v.z = v1.z + v2.z;
	return (new_v);
}

t_vector	subtract_points(t_point p1, t_point p2)
{
	t_vector    v;

	v.x = p1.x - p2.x;
	v.y = p1.y - p2.y;
	v.z = p1.z - p2.z;
	return (v);
}

t_vector	scale_vector(t_vector v, double factor)
{
	t_vector	new_v;

	new_v.x = v.x * factor;
	new_v.y = v.y * factor;
	new_v.z = v.z * factor;
	return (new_v);
}

t_vector negate_vector(t_vector v)
{
	return (scale_vector(v, -1));
}
