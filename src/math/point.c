#include "minirt_math.h"

t_point create_point(double x, double y, double z)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_point add_v_to_p(t_point p, t_vector v)
{
	t_point	new_p;

	new_p.x = p.x + v.x;
	new_p.y = p.y + v.y;
	new_p.z = p.z + v.z;
	return (new_p);
}

t_point	minus_v_from_p(t_point p, t_vector v)
{
	t_point	new_p;

	new_p.x = p.x - v.x;
	new_p.y = p.y - v.y;
	new_p.z = p.z - v.z;
	return (new_p);
}
