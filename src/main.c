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
	t_mlx_vars env;

	if (ac != 1) // change to 2
	{
		printf("Input scenes/<filename>.rt as 2nd argument\n");
		return (1);
	}
	(void)av;
	if (init_env(&env))
		return (1);

	// Intersect test
	// t_ray		r = create_ray(create_point(0, 2, -5), create_vec4d(0, 0, 1));
	// t_object	s;
	// t_itx_set	xs;

	// s.type = SPHERE;
	// s.inv_transform = identity_mat();
	// s.center = create_point(0, 0, 0);
	// xs.count = 0;
	// intersect_sphere(&r, &s, &xs);
	// printf("count: %d\n xs[0]: %.1f\n xs[1]: %.1f\n", xs.count, xs.arr[0].t, xs.arr[1].t);

	// Transform ray test
	// t_ray	r = create_ray(create_point(1, 2, 3), create_vec4d(0, 1, 0));
	// t_mat4d	m = scaling_mat(2, 3, 4);
	// t_ray	r2 = r;

	// transform_ray(&r2, &m);
	// printf("%.0f, %.0f, %.0f\n", r2.origin.x, r2.origin.y, r2.origin.z);
	// printf("%.0f, %.0f, %.0f\n", r2.direction.x, r2.direction.y, r2.direction.z);

	// Intersect with transform test
	// t_ray		r = create_ray(create_point(0, 0, -5), create_vec4d(0, 0, 1));
	// t_object	s;
	// t_itx_set	xs;

	// s.type = SPHERE;
	// s.transform = translation_mat(5, 0, 0);
	// s.inv_transform = inverse_mat4d(s.transform);
	// s.center = create_point(5, 0, 0);
	// intersect_sphere(&r, &s, &xs);
	// printf("count: %d\n xs[0]: %.1f\n xs[1]: %.1f\n", xs.count, xs.arr[0].t, xs.arr[1].t);

// Hit test
	// t_object	s;
	// t_itx		i1;
	// t_itx		i2;
	// t_itx		i3;
	// t_itx		i4;
	// t_itx_set	xs;
	// t_itx		*hit_itx;

	// s.type = SPHERE;
	// i1.t = 5;
	// i1.obj = &s;
	// i2.t = 7;
	// i2.obj = &s;
	// i3.t = -3;
	// i3.obj = &s;
	// i4.t = 2;
	// i4.obj = &s;
	// xs.arr[0] = i1;
	// xs.arr[1] = i2;
	// xs.arr[2] = i3;
	// xs.arr[3] = i4;
	// xs.count = 4;

	// hit_itx	= hit(&xs, SPHERE);
	// printf("t: %f\n", hit_itx->t);

// Draw circle test
	// t_ray		r;
	// t_point		r_origin = create_point(0, 0, -5);
	// t_object	s;
	// t_itx_set	xs;
	// t_point		position;
	// t_shear		shear = {0};
	// int			y;
	// int			x;
	// float		world_y;
	// float		world_x;
	// float		pixel_size;

	// s.type = SPHERE;
	// shear.x_y = 1;
	// s.transform = scaling_mat(1, 1, 1);
	// s.inv_transform = inverse_mat4d(s.transform);
	// // s.inv_transform = identity_mat();
	// s.center = create_point(0, 0, 0);
	// xs.count = 0;
	// x = -1;
	// y = -1;
	// pixel_size = 1;
	// while (++y < WINDOW_H - 1)
	// {
	// 	world_y = HALF_H - y * pixel_size;
	// 	while (++x < WINDOW_W - 1)
	// 	{
	// 		world_x = -HALF_W + x * pixel_size;
	// 		position = create_point(world_x, world_y, 100);
	// 		r = create_ray(r_origin, normalize(subtract_points(position, r_origin)));
	// 		if (intersect_sphere(&r, &s, &xs))
	// 			draw(&env, x, y, OLIVE);
	// 		else
	// 			draw(&env, x, y, BLACK);
	// 		xs.count = 0;
	// 	}
	// 	x = -1;
	// }

// Draw circle with lighting and shading
	t_ray		r;
	t_point		r_origin = create_point(0, 0, -5);
	t_object	s;
	t_itx_set	xs;
	t_point		pixel_pos;
	t_shear		shear = {0};
	t_material	m;
	t_light		light;
	t_color		black;
	t_color		pixel_color;
	t_point		point;
	t_vec4d		eye_v;
	t_vec4d		normal;
	int			y;
	int			x;
	float		world_y;
	float		world_x;

	s.type = SPHERE;
	shear.x_y = 1;
	s.transform = scaling_mat(1, 1, 1);
	s.inv_transform = inverse_mat4d(s.transform);
	// s.inv_transform = identity_mat();
	s.center = create_point(0, 0, 0);
	xs.count = 0;
	x = -1;
	y = -1;
	m.color = create_color(255, 0.2 * 255, 255);
	printf("%u\n", plot_color(m.color));
	s.material = m;
	light.position = create_point(-10, 10, -10);
	light.color = create_color(255, 255, 255);
	black = create_color(0, 0, 0);
	while (++y < WINDOW_H - 1)
	{
		world_y = HALF_H - y;
		while (++x < WINDOW_W - 1)
		{
			world_x = -HALF_W + x;
			pixel_pos = create_point(world_x, world_y, 150);
			r = create_ray(r_origin, normalize(subtract_points(pixel_pos, r_origin)));
			if (intersect_sphere(&r, &s, &xs))
			{
				point = position(&r, hit(&xs, SPHERE)->t);
				eye_v = negate_vector(r.direction);
				normal = normal_at(&s, &point);
				pixel_color = lighting(&s, &light, &point, &eye_v, &normal);
				draw(&env, x, y, pixel_color);
			}
			else
				draw(&env, x, y, black);
			xs.count = 0;
		}
		x = -1;
	}

	mlx_put_image_to_window(env.mlx, env.win, env.img, 0, 0);
	mlx_loop(env.mlx);
	return (0);
}
