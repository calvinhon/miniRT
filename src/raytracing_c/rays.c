#include "minirt.h"

<<<<<<< HEAD
t_ray	create_ray(t_point origin, t_vec4d direction)
=======
t_point position(t_ray *r, float t)
{
	return (add_v_to_p(r->origin, scale_vector(r->direction, t)));
}

t_ray create_ray(t_point *origin, t_vec4d *direction)
>>>>>>> ed472181482a524413cb6122dc67ea5c971f55cf
{
	t_ray r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

void transform_ray(t_ray *r, t_mat4d *m)
{
	r->origin = mult_mat4d_pt4d(*m, r->origin);
	r->direction = mult_mat4d_vec4d(*m, r->direction);
}