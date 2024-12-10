#include "minirt_math.h"

t_point create_point(double x, double y, double z)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = z;
	p.p = 1;
	return (p);
}

t_point add_v_to_p(t_point p, t_vector v)
{
	return (create_point(p.x + v.x, p.y + v.y, p.z + v.z));
}

t_point	minus_v_from_p(t_point p, t_vector v)
{
	return (create_point(p.x - v.x, p.y - v.y, p.z - v.z));
}
