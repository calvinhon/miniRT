#include "miniRT.h"

t_itx_grp local_intersect(t_scene *s, t_ray *r)
{
	t_itx_grp xs;
	int i;

	i = -1;
	xs.count = 0;
	while (++i < s->num_shapes)
	{
		if (s->shapes[i].type == SPHERE && xs.count + 2 <= MAX_ITX)
			intersect_sphere(r, &s->shapes[i], &xs);
		else if (s->shapes[i].type == PLANE && xs.count + 1 <= MAX_ITX)
			intersect_plane(r, &s->shapes[i], &xs);
		else if (s->shapes[i].type == CYLINDER && xs.count + 2 <= MAX_ITX)
			intersect_cylinder(r, &s->shapes[i], &xs);
		// else if (s->shapes[i].type == CUBE)
		// 	intersect_cube(r, &s->shapes[i], &xs);
		// else if (s->shapes[i].type == CONE)
		// 	intersect_cone(r, &s->shapes[i], &xs);
	}
	return (xs);
}