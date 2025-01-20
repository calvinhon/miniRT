#include "minirt.h"

t_vec4d sphere_normal_at(t_object *o, t_point *wrld_p)
{
	t_point obj_pt;
	t_vec4d obj_normal;
	t_vec4d wrld_normal;
	t_mat4d transposed;

	obj_pt = mult_mat4d_pt4d(o->inv_transform, *wrld_p);
	obj_normal = subtract_points(obj_pt, create_point(0, 0, 0));
	transposed = transpose_mat4d(o->inv_transform);
	wrld_normal = mult_mat4d_vec4d(transposed, obj_normal);
	return (normalize(wrld_normal));
}

bool intersect_sphere(t_ray *r, t_object *o, t_itx_set *xs)
{
	float d;
	t_ray trans_r;
	t_vec4d o_to_ray;
	t_vec4d abc;

	if (xs->count + 2 >= _RT_MAX_ITX)
		return (false);
	trans_r = *r;
	transform_ray(&trans_r, &o->inv_transform);
	o_to_ray = subtract_points(trans_r.origin, o->center);
	abc.x = dot(trans_r.direction, trans_r.direction);
	abc.y = 2.f * dot(trans_r.direction, o_to_ray);
	abc.z = dot(o_to_ray, o_to_ray) - 1.f;
	d = abc.y * abc.y - 4.f * abc.x * abc.z;
	if (d < 0)
		return (false);
	d = sqrtf(d);
	xs->arr[xs->count].obj = o;
	xs->arr[xs->count++].t = (-abc.y - d) / (2.f * abc.x);
	xs->arr[xs->count].obj = o;
	xs->arr[xs->count++].t = (-abc.y + d) / (2.f * abc.x);
	return (true);
}
