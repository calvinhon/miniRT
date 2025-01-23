#include "minirt.h"

t_itx_set local_intersect(t_scene *s, t_ray *r)
{
	t_itx_set xs;
	int i;

	i = -1;
	xs.count = 0;
	while (++i < s->num_shapes)
	{
		if (s->objs[i].type == SPHERE && xs.count + 2 <= MAX_ITX)
			intersect_sphere(r, &s->objs[i], &xs);
		else if (s->objs[i].type == PLANE && xs.count + 1 <= MAX_ITX)
			intersect_plane(r, &s->objs[i], &xs);
		else if (s->objs[i].type == CYLINDER && xs.count + 2 <= MAX_ITX)
			intersect_cylinder(r, &s->objs[i], &xs);
		// else if (s->objs[i].type == CUBE)
		// 	intersect_cube(r, &s->objs[i], &xs);
		// else if (s->objs[i].type == CONE)
		// 	intersect_cone(r, &s->objs[i], &xs);
	}
	return (xs);
}