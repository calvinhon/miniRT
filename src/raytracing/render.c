#include "minirt.h"

t_ray	create_ray(t_point origin, tvec)
{

}

t_ray	cam_ray_to_pixel(t_camera *cam, int x, int y)
{
	t_vec4d	pixel_cam;
	t_vec4d	pixel_world;
	t_vec4d	cam_origin_world;
	t_vec4d	ray_direction;

	// lag_vec4dp_init(&op, (cam->half_width - (x + 0.5f) * cam->pixel_size),
	// 	(cam->half_height - (y + 0.5f) * cam->pixel_size), -1);
	// lag_mat4s_cross_vec4d(&cam->inv_transform, &op, &pixel);
	// lag_vec4dp_init(&op, 0.f, 0.f, 0.f);
	// lag_mat4s_cross_vec4d(&cam->inv_transform, &op, &origin);
	// lag_vec4d_sub(&direction, &pixel, &origin);
	// lag_vec4d_normalize(&direction);
	pixel_cam = create_vec4d((cam->half_width - (x + 0.5f) * cam->pixel_size),
		(cam->half_height - (y + 0.5f) * cam->pixel_size), -1)
	pixel_world = cross(cam->inv_transform, pixel_cam);
	cam_origin_world = cross(cam->inv_transform, create_vec4d(0, 0, 0));
	ray_direction = normalize(subtract_vectors(pixel_world, cam_origin_world));
	return (ray_create(camori, &direction));
}

t_color	render_pixel(t_minirt *vars, int x, int y)
{
	t_ray		r;
	t_color		c;

	r = cam_ray_to_pixel(&vars->cam, x, y);
	c = color_at(&vars->world, &r, _RT_REFLECTION_DEPTH);
	put_pixel(&vars->canvas, x, y, &c);
	return (c);
}
