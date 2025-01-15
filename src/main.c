/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:44:06 by chon              #+#    #+#             */
/*   Updated: 2024/12/11 14:44:06 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Scaling matrix can't have 0 as an input

int init_env(t_mlx_vars *env)
{
	env->mlx = mlx_init();
	if (!env->mlx)
	{
		printf("Error initializing mlx\n");
		return (1);
	}
	env->win = mlx_new_window(env->mlx, WINDOW_W, WINDOW_H, "Rayineers' miniRT");
	env->img = mlx_new_image(env->mlx, WINDOW_W, WINDOW_H);
	env->addr = mlx_get_data_addr(env->img, &env->bpp, &env->l_len, &env->end);
	env->bpp_8 = env->bpp / 8;
	if (!env->win || !env->img || !env->addr)
		return (1);
	// ft_bzero(env->addr, WINDOW_W * WINDOW_H * env->bpp_8);
	set_controls(env);
	return (0);
}

int main(int ac, char **av)
{
	t_minirt	program;
	t_mlx_vars	env;

	if (ac != 1) // change to 2
	{
		printf("Input scenes/<filename>.rt as 2nd argument\n");
		return (1);
	}
	(void)av;
	if (init_env(&program.env))
		return (1);

// Draw circle with lighting and shading
	// t_ray		r;
	// t_point		r_origin = create_point(0, 0, -5);
	// t_object	s;
	// t_itx_set	xs;
	// t_point		pixel_pos;
	// // t_shear		shear = {0};
	// t_material	m;
	// t_light		light;
	// t_color		black;
	// t_color		pixel_color;
	// t_point		point;
	// t_vec4d		eye_v;
	// t_vec4d		normal;
	// int			y;
	// int			x;
	// float		world_y;
	// float		world_x;

	// s.type = SPHERE;
	// // shear.x_y = 1;
	// s.transform = scaling_mat(1, 1, 1);
	// s.inv_transform = inverse_mat4d(s.transform);
	// // s.inv_transform = identity_mat();
	// s.center = create_point(0, 0, 0);
	// xs.count = 0;
	// x = -1;
	// y = -1;
	// m.ambient.color = create_color(.1, .1, .1);
	// m.diffuse = create_color(.9, .9, .9);
	// m.specular = create_color(.9, .9, .9);
	// m.shininess = 200;
	// m.color = create_color(255, 0.2 * 255, 255);
	// s.material = m;
	// light.position = create_point(10, -10, -10);
	// light.color = create_color(1, 1, 1);
	// black = create_color(0, 0, 0);
	// while (++y < WINDOW_H - 1)
	// {
	// 	world_y = HALF_H - y;
	// 	while (++x < WINDOW_W - 1)
	// 	{
	// 		world_x = -HALF_W + x;
	// 		pixel_pos = create_point(world_x, world_y, 1000);
	// 		r = create_ray(r_origin, normalize(subtract_points(pixel_pos, r_origin)));
	// 		if (intersect_sphere(&r, &s, &xs))
	// 		{
	// 			point = position(&r, hit(&xs)->t);
	// 			normal = sphere_normal_at(&s, &point);
	// 			eye_v = negate_vector(r.direction);
	// 			pixel_color = lighting(&s, &light, &point, &eye_v, &normal);
	// 			draw(&env, x, y, pixel_color);
	// 		}
	// 		else
	// 			draw(&env, x, y, black);
	// 		xs.count = 0;
	// 	}
	// 	x = -1;
	// }

// Color_at test
	// t_scene		scene;
	// t_light		l;
	// t_object	o[2];
	// t_object	s1;
	// t_object	s2;
	// t_material	m;
	// t_ray		r;
	// t_color		color;

	// l.position = create_point(-10, 10, -10);
	// l.color = create_color(1, 1, 1);
	// scene.lights = &l;
	// m.shininess = 200;
	// m.color = scale_color(create_color(0.8, 1, 0.6), 255);
	// m.ambient.color = create_color(0.1, 0.1, 0.1);
	// // m.ambient.color = create_color(0.8, 1, 0.6);
	// m.diffuse = create_color(0.7, 0.7, 0.7);
	// m.specular = create_color(0.2, 0.2, 0.2);
	// s1.material = m;
	// s1.center = create_point(0, 0, 0);
	// s1.inv_transform = identity_mat();
	// s1.type = SPHERE;
	// o[0] = s1;
	// s2.center = create_point(0, 0, 0);
	// s2.transform = scaling_mat(0.5, 0.5, 0.5);
	// s2.inv_transform = inverse_mat4d(s2.transform);
	// s2.type = SPHERE;
	// o[1] = s2;
	// scene.objs = o;
	// scene.num_lights = 1;
	// scene.num_shapes = 2;
	// r = create_ray(create_point(0, 0, 0.75), create_vec4d(0, 0, -1));
	// color = scale_color(color_at(&scene, &r, 2), (float)1 / 255);
	// printf("%f, %f, %f\n", color.r, color.g, color.b);

// Making a scene with shadows test
	int			y;
	int			x;
	t_scene		s;
	t_light		l[1];
	t_light		l1;
	l1.position = create_point(-10, 10, -10);
	l1.color = create_color(1, 1, 1);
	l[0] = l1;
	s.lights = l;
	t_material	m;
	m.ambient.color = create_color(.1, .1, .1);
	m.diffuse = create_color(.9, .9, .9);
	m.specular = create_color(0, 0, 0);
	m.shininess = 200;
	t_camera	cam;
	cam = set_camera(PI/3);
	cam.transform = view_transform(create_point(0, 1.5, -5), create_point(0, 1, 0), create_vec4d(0, 1, 0));
	cam.inv_transform = inverse_mat4d(cam.transform);
	program.cam = cam;
	t_object	o[6];
	t_object	floor;
	floor.type = SPHERE;
	floor.center = create_point(0, 0, 0);
	floor.transform = scaling_mat(10, 0.01, 10);
	floor.inv_transform = inverse_mat4d(floor.transform);
	floor.material = m;
	floor.material.color = scale_color(create_color(1, 0.9, 0.9), 255);
	o[0] = floor;
	t_object	left_wall;
	left_wall.type = SPHERE;
	left_wall.center = create_point(0, 0, 0);
	left_wall.transform = mult_n_mat4d(4, scaling_mat(10, 0.01, 10), rotate_mat_x(PI/2), rotate_mat_y(-PI/4), translation_mat(0, 0, 5));
	left_wall.inv_transform = inverse_mat4d(left_wall.transform);
	left_wall.material = floor.material;
	o[1] = left_wall;
	t_object	right_wall;
	right_wall.type = SPHERE;
	right_wall.center = create_point(0, 0, 0);
	right_wall.transform = mult_n_mat4d(4, scaling_mat(10, 0.01, 10), rotate_mat_x(PI/2), rotate_mat_y(PI/4), translation_mat(0, 0, 5));
	right_wall.inv_transform = inverse_mat4d(right_wall.transform);
	right_wall.material = floor.material;
	o[2] = right_wall;
	t_material	sphere_m;
	sphere_m.ambient.color = create_color(.1, .1, .1);
	sphere_m.diffuse = create_color(0.7, 0.7, 0.7);
	sphere_m.specular = create_color(0.3, 0.3, 0.3);
	sphere_m.shininess = 200;
	t_object	middle;
	middle.type = SPHERE;
	middle.center = create_point(0, 0, 0);
	middle.material = sphere_m;
	middle.material.color = scale_color(create_color(0.1, 1, 0.5), 255);
	middle.transform = translation_mat(-0.5, 1, 0.5);
	middle.inv_transform = inverse_mat4d(middle.transform);
	o[3] = middle;
	t_object	right;
	right.type = SPHERE;
	right.center = create_point(0, 0, 0);
	right.material = sphere_m;
	right.material.color = scale_color(create_color(0.5, 1, 0.1), 255);
	right.transform = mult_n_mat4d(2, scaling_mat(0.5, 0.5, 0.5), translation_mat(1.5, 0.5, -0.5));
	right.inv_transform = inverse_mat4d(right.transform);
	o[4] = right;
	t_object	left;
	left.type = SPHERE;
	left.center = create_point(0, 0, 0);
	left.material = sphere_m;
	left.material.color = scale_color(create_color(1, 0.8, 0.1), 255);
	left.transform = mult_n_mat4d(2, scaling_mat(0.33, 0.33, 0.33), translation_mat(-1.5, 0.33, -0.75));
	left.inv_transform = inverse_mat4d(left.transform);
	o[5] = left;
	s.objs = o;
	s.num_shapes = 6;
	s.num_lights = 1;
	program.scene = s;
	y = -1;
	x = -1;
	while (++y < cam.vsize - 1)
	{
		while (++x < cam.hsize - 1)
		{
			render_pixel(&program, x, y);
		}
		x = -1;
	}
	env = program.env;
	mlx_put_image_to_window(env.mlx, env.win, env.img, 0, 0);
	mlx_loop(env.mlx);
	return (0);
}
