#include "minirt.h"

float check_cap(t_ray *r, float t, float radius)
{
	float x;
	float z;

	x = r->origin.x + t * r->direction.x;
	z = r->origin.z + t * r->direction.z;
	return (x * x + z * z <= radius + EPSILON);
}

void intersect_caps(t_ray *r, t_object *o, t_itx_grp *xs, bool is_cone)
{
	float t;
	float radius;

	if (!o->specs.closed || fabsf(r->direction.y) < EPSILON)
		return;
	if (is_cone)
		radius = fabsf(o->specs.min_y);
	else
		radius = 1;
	t = (o->specs.min_y - r->origin.y) / r->direction.y;
	if (check_cap(r, t, radius))
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t;
	}
	if (is_cone)
		radius = fabsf(o->specs.max_y);
	t = (o->specs.max_y - r->origin.y) / r->direction.y;
	if (check_cap(r, t, radius))
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t;
	}
}

void check_y_values(float *t, t_ray *r, t_object *o, t_itx_grp *xs)
{
	float y;

	swap(t);
	y = r->origin.y + t[0] * r->direction.y;
	if (y > o->specs.min_y && y < o->specs.max_y)
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t[0];
	}
	y = r->origin.y + t[1] * r->direction.y;
	if (y > o->specs.min_y && y < o->specs.max_y)
	{
		xs->arr[xs->count].obj = o;
		xs->arr[xs->count++].t = t[1];
	}
}

void swap(float *t)
{
	if (t[0] > t[1])
	{
		t[2] = t[0];
		t[0] = t[1];
		t[1] = t[2];
	}
}
