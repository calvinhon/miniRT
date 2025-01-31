#include "minirt.h"

t_vec4d cone_normal_at(t_object *o, t_point *wrld_p)
{
	t_point obj_p;
	t_vec4d obj_normal;
	t_mat4d transposed;
	t_vec4d wrld_normal;
	float dist;

	if (wrld_p->x == 0 && wrld_p->y == 0 && wrld_p->z == 0)
		return (create_vec4d(0, 0, 0));
	obj_p = mult_mat4d_pt4d(&o->inv_transform, wrld_p);
	dist = pow(obj_p.x, 2) + pow(obj_p.z, 2);
	if (dist < 1 && obj_p.y >= o->specs.max_y - EPSILON)
		obj_normal = create_vec4d(0, 1, 0);
	else if (dist < 1 && obj_p.y <= o->specs.min_y + EPSILON)
		obj_normal = create_vec4d(0, -1, 0);
	else
	{
		dist = sqrt(dist);
		if (obj_p.y > 0)
			dist *= -1;
		obj_normal = create_vec4d(obj_p.x, dist, obj_p.z);
	}
	transposed = transpose_mat4d(&o->inv_transform);
	wrld_normal = mult_mat4d_vec4d(&transposed, &obj_normal);
	return (normalize(&wrld_normal));
}

void	calc_abc(t_vec4d *abc, t_ray *r)
{
	abc->x = pow(r->direction.x, 2) - pow(r->direction.y, 2)
		+ pow(r->direction.z, 2);
	abc->y = 2 * (r->origin.x * r->direction.x
		- r->origin.y * r->direction.y
		+ r->origin.z * r->direction.z);
	abc->z = pow(r->origin.x, 2) - pow(r->origin.y, 2)
		+ pow(r->origin.z, 2);
}

void intersect_cone(t_ray *r, t_object *o, t_itx_grp *xs)
{
	t_ray	trfm_r;
	t_vec4d abc;
	float 	d;
	float	t[3];

	trfm_r = *r;
	transform_ray(&trfm_r, &o->inv_transform);
	intersect_caps(&trfm_r, o, xs, 1);
	calc_abc(&abc, &trfm_r);
	if (!abc.x && !abc.y)
		return ;
	if (!abc.x)
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = -abc.z / (2 * abc.y);
		return ;
	}
	d = abc.y * abc.y - 4 * abc.x * abc.z;
	if (d < -EPSILON)
		return ;
	if (d > 0)
		d = sqrtf(d);
	abc.x *= 2.f;
	t[0] = (-abc.y - d) / abc.x;
	t[1] = (-abc.y + d) / abc.x;
	check_y_values(t, &trfm_r, o, xs);
}
