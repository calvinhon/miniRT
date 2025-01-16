#include "minirt.h"

bool	intersect_sphere(t_ray *r, t_object *sphere, t_itx_set *xs)
{
	float	d;
	t_ray	trans_r;
	t_vec4d	sphere_to_ray;
	t_vec4d	abc;

	if (xs->count + 2 >= _RT_MAX_ITX)
		return (false);
	trans_r = *r;
	transform_ray(&trans_r, &sphere->inv_transform);
	sphere_to_ray = subtract_points(trans_r.origin, sphere->center);
	abc.x = dot(trans_r.direction, trans_r.direction);
	abc.y = 2.f * dot(trans_r.direction, sphere_to_ray);
	abc.z = dot(sphere_to_ray, sphere_to_ray) - 1.f;
	d = abc.y * abc.y - 4.f * abc.x * abc.z;
	if (d < 0)
		return (false);
	d = sqrtf(d);
	xs->arr[xs->count].obj = sphere;
	xs->arr[xs->count++].t = (-abc.y - d) / (2.f * abc.x);
	xs->arr[xs->count].obj = sphere;
	xs->arr[xs->count++].t = (-abc.y + d) / (2.f * abc.x);
	return (true);
}
