#include "minirt_math.h"

t_vec4d add_vectors(t_vec4d v1, t_vec4d v2)
{
	return (create_vec4d(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vec4d subtract_points(t_point p1, t_point p2)
{
	return (create_vec4d(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z));
}

t_vec4d	subtract_vectors(t_vec4d v1, t_vec4d v2)
{
	return (create_vec4d(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vec4d scale_vector(t_vec4d v, double factor)
{
	return (create_vec4d(v.x * factor, v.y * factor, v.z * factor));
}

t_vec4d negate_vector(t_vec4d v)
{
	return (scale_vector(v, -1));
}
