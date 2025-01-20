#include "minirt.h"

t_itx *get_hit(t_itx_set *xs)
{
	int i;
	t_itx *itx;
	float t0;

	i = -1;
	itx = NULL;
	t0 = FLT_MAX;
	while (++i < xs->count)
	{
		if (xs->arr[i].t < t0 && xs->arr[i].t > EPSILON)
		{
			itx = &xs->arr[i];
			t0 = xs->arr[i].t;
		}
	}
	return (itx);
}

void local_normal_at(t_itx *itx, t_comps *comps)
{
	if (itx->obj->type == SPHERE)
		comps->normal_v = sphere_normal_at(itx->obj, &comps->p);
	else if (itx->obj->type == PLANE)
		comps->normal_v = plane_normal_at(itx->obj, &comps->p);
	// else if (itx->obj->type == CYLINDER)
	// 	comps->normal_v = cylinder_normal_at(itx->obj, &comps->p);
	// else if (itx->obj->type == CUBE)
	// 	comps->normal_v = cube_normal_at(itx->obj, &comps->p);
	// else if (itx->obj->type == CONE)
	// 	comps->normal_v = cone_normal_at(itx->obj, &comps->p);
	if (dot(comps->normal_v, comps->eye_v) < EPSILON)
	{
		comps->inside = true;
		comps->normal_v = negate_vector(comps->normal_v);
	}
	else
		comps->inside = false;
}

t_comps prepare_computations(t_itx *itx, t_ray *r, t_itx_set *xs)
{
	float bump;
	t_comps comps;
	// t_vec4d		margin;

	comps.t = itx->t;
	comps.obj = itx->obj;
	comps.p = position(r, comps.t);
	comps.eye_v = negate_vector(r->direction);
	local_normal_at(itx, &comps);
	// adjust bump based on object thickness for spheres
	bump = EPSILON * 10;
	comps.over_point = add_v_to_p(comps.p, scale_vector(comps.normal_v, bump));
	// lag_vec4s_scaleby(&margin, comps.normal_v, bump);
	// lag_vec4s_sub(&comps.under_point, &comps.p, &margin);
	// comps.reflectv = reflect(&r->dir, &comps.normal_v);
	// if (comps.obj->material.refractive_index > 0.f)
	// 	prepare_refractions(itx, &comps, xs);
	(void)xs;
	return (comps);
}

t_color color_at(t_scene *s, t_ray *r, int depth)
{
	t_itx_set world_itxs;
	t_itx *hit;
	t_comps comps;

	world_itxs = local_intersect(s, r);
	hit = get_hit(&world_itxs);
	if (!hit)
		return (create_color(0, 0, 0));
	comps = prepare_computations(hit, r, &world_itxs);
	return (shade_hit(s, &comps, depth));
}

t_ray cam_ray_to_pixel(t_camera *cam, int px, int py)
{
	t_point pixel_cam;
	t_point pixel_world;
	t_point cam_origin_world;
	t_vec4d ray_direction;

	pixel_cam = create_point((cam->half_width - (px + 0.5f) * cam->pixel_size),
							 (cam->half_height - (py + 0.5f) * cam->pixel_size), -1);
	pixel_world = mult_mat4d_pt4d(cam->inv_transform, pixel_cam);
	cam_origin_world = mult_mat4d_pt4d(cam->inv_transform, create_point(0, 0, 0));
	ray_direction = normalize(subtract_points(pixel_world, cam_origin_world));
	return (create_ray(&cam_origin_world, &ray_direction));
}

t_color render_pixel(t_minirt *program, int x, int y)
{
	t_ray r;
	t_color c;

	r = cam_ray_to_pixel(&program->cam, x, y);
	c = color_at(&program->scene, &r, MAX_RFLX);
	draw(&program->env, x, y, &c);
	return (c);
}
