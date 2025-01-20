#include "minirt.h"

t_itx_set local_intersect(t_scene *s, t_ray *r)
{
	t_itx_set set;
	int i;

	i = -1;
	set.count = 0;
	while (++i < s->num_shapes)
	{
		if (set.count >= MAX_ITX)
			break;
		if (s->objs[i].type == SPHERE)
			intersect_sphere(r, &s->objs[i], &set);
		else if (s->objs[i].type == PLANE)
			intersect_plane(r, &s->objs[i], &set);
		// else if (s->objs[i].type == CYLINDER)
		// 	intersect_cylinder(r, &s->objs[i], &set);
		// else if (s->objs[i].type == CUBE)
		// 	intersect_cube(r, &s->objs[i], &set);
		// else if (s->objs[i].type == CONE)
		// 	intersect_cone(r, &s->objs[i], &set);
	}
	return (set);
}