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

void	draw(t_mlx_vars *env);

int	init_env(t_mlx_vars *env)
{
	env->mlx = mlx_init();
	if (!env->mlx)
	{
		printf("Error initializing mlx\n");
		return (1);
	}
	env->win = mlx_new_window(env->mlx, WINDOW_W, WINDOW_L, "Rayineers' miniRT");
	env->img = mlx_new_image(env->mlx, WINDOW_W, WINDOW_L);
	env->addr = mlx_get_data_addr(env->img, &env->bpp, &env->l_len, &env->end);
	if (!env->win || !env->img || !env->addr)
		return (1);
	set_controls(env);
	return (0);
}

int main(int ac, char **av)
{
	// t_mlx_vars	env;

	if (ac != 1) // change to 2
	{
		printf("Input scenes/<filename>.rt as 2nd argument\n");
		return (1);
	}
	(void)av;
	// if (init_env(&env))
	// 	return (1);
	// draw(&env);
	// mlx_loop(env.mlx);

// Normal
	// t_sphere s;
	// s.transform = mult_2x_mat4d(scaling_mat(1, 0.5, 1), rotate_mat_z(M_PI/5));
	// t_point p = create_point(0, sqrt(2)/2, -sqrt(2)/2);
	// t_vec4d norm = normal_at(s, p);
	// printf("%.4f, %.4f, %.4f\n", norm.x, norm.y, norm.z);

// Reflection
	// t_vec4d v = create_vec4d(0, -1, 0);
	// t_vec4d n = create_vec4d(sqrt(2)/2, sqrt(2)/2, 0);
	// t_vec4d r = reflect(v, n);
	// printf("%.4f, %.4f, %.4f\n", r.x, r.y, r.z);

// Phong
	// t_point	p = create_point(0, 0, 0);
	// t_vec4d e = create_vec4d(0, 0, -1);
	// t_light l;
	// l.position = create_point(0, 0, 10);
	// l.color = create_color(1, 1, 1);
	// t_sphere s;
	// s.transform = identity_mat();
	// s.material.color = create_color(1, 1, 1);
	// s.material.ambient.color = create_color(.1, .1, .1);
	// s.material.diffuse = create_color(0.9, 0.9, 0.9);
	// s.material.specular = create_color(0.9, 0.9, 0.9);
	// s.material.shininess = 200;
	// t_color c = lighting(s, l, p, e);
	// printf("%.4f, %.4f, %.4f\n", c.r, c.g, c.b);

	return (0);
}
