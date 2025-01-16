#include "minirt.h"

t_ray	create_ray(t_point origin, t_vec4d direction)
{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}

void	transform_ray(t_ray *r, t_mat4d *m)
{
	r->origin = mult_mat4d_pt4d(*m, r->origin);
	r->direction = mult_mat4d_vec4d(*m, r->direction);
}