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

void draw(t_mlx_vars *env);

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
	if (!env->win || !env->img || !env->addr)
		return (1);
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
	t_object	s;
	t_itx		i1;
	t_itx		i2;
	t_itx		i3;
	t_itx		i4;
	t_itx_set	xs;
	t_itx		*hit_itx;

	s.type = SPHERE;
	i1.t = 5;
	i1.obj = &s;
	i2.t = 7;
	i2.obj = &s;
	i3.t = -3;
	i3.obj = &s;
	i4.t = 2;
	i4.obj = &s;
	xs.arr[0] = i1;
	xs.arr[1] = i2;
	xs.arr[2] = i3;
	xs.arr[3] = i4;
	xs.count = 4;

	hit_itx	= hit(&xs, SPHERE);
	printf("t: %f\n", hit_itx->t);

// Draw circle test
	// t_ray		r = create_ray(create_point(0, 0, -5), create_vec4d(0, 0, 1));
	// t_object	s;
	// t_itx_set	xs;

	// s.type = SPHERE;
	// s.inv_transform = identity_mat();
	// s.center = create_point(0, 0, 0);

	ft_bzero(env.addr, WINDOW_W * WINDOW_H * (env.bpp / 8));
	draw(&env);
	mlx_loop(env.mlx);
	return (0);
}
