#include "minirt.h"

t_itx	*hit(t_itx_set *xs, t_objtype objtype)
{
	int		i;
	t_itx	*itx;
	float	t0;

	i = -1;
	itx = NULL;
	t0 = FLT_MAX;
	while (++i < xs->count)
	{
		if (xs->arr[i].obj->type == objtype && xs->arr[i].t < t0
			&& xs->arr[i].t > 0)
		{
			itx = &xs->arr[i];
			t0 = xs->arr[i].t;
		}
	}
	return (itx);
}

t_ray	cam_ray_to_pixel(t_camera *cam, int px, int py)
{
	t_point	pixel_cam;
	t_point	pixel_world;
	t_point	cam_origin_world;
	t_vec4d	ray_direction;

	pixel_cam = create_point((cam->half_width - (px + 0.5f) * cam->pixel_size),
		(cam->half_height - (py + 0.5f) * cam->pixel_size), -1);
	pixel_world = mult_mat4d_pt4d(cam->inv_transform, pixel_cam);
	cam_origin_world = mult_mat4d_pt4d(cam->inv_transform, create_point(0, 0, 0));
	ray_direction = normalize(subtract_points(pixel_world, cam_origin_world));
	return (create_ray(cam_origin_world, ray_direction));
}

t_color	render_pixel(t_minirt *vars, int x, int y)
{
	t_ray	r;
	// t_color	c;

	r = cam_ray_to_pixel(&vars->cam, x, y);
	(void)r;
	// c = color_at(&vars->world, &r, _RT_REFLECTION_DEPTH);
	// put_pixel(&vars->canvas, x, y, &c);
	// return (c);
	return (create_color(1, 1, 1));
}
