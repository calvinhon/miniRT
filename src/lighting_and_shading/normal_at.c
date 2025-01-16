#include "minirt.h"

t_vec4d	sphere_normal_at(t_object *o, t_point *wrld_p)
{
	t_point	obj_pt;
	t_vec4d	obj_normal;
	t_vec4d	wrld_normal;
	t_mat4d	transposed;

	obj_pt = mult_mat4d_pt4d(o->inv_transform, *wrld_p);
	obj_normal = subtract_points(obj_pt, create_point(0, 0, 0));
	transposed = transpose_mat4d(o->inv_transform);
	wrld_normal = mult_mat4d_vec4d(transposed, obj_normal);
	wrld_normal.p = 0;
	return (normalize(wrld_normal));
}
