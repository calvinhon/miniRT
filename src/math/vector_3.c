#include "minirt_math.h"

t_vec4d add_vectors(const t_vec4d *v1, const t_vec4d *v2)
{
	return (create_vec4d(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z));
}

t_vec4d subtract_points(const t_point *p1, const t_point *p2)
{
	return (create_vec4d(p1->x - p2->x, p1->y - p2->y, p1->z - p2->z));
}

t_vec4d subtract_vectors(const t_vec4d *v1, const t_vec4d *v2)
{
	return (create_vec4d(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z));
}

void	scale_vector(t_vec4d *out, const t_vec4d *v, float factor)
{
	*out = create_vec4d(v->x * factor, v->y * factor, v->z * factor);
}

t_vec4d negate_vector(const t_vec4d *v)
{	
	t_vec4d	out;

	scale_vector(&out, v, -1);
	return (out);
}
