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
#include "minirt_math.h"

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

	// t_vec4d v1;
	// t_vec4d v2;
	// t_vec4d v3;
	// t_vec4d v4;
	// t_vec4d v5;
	// t_vec4d v6;
	// t_mat4d m1;
	// t_mat4d m2;
	// t_mat4d m3;

	// v1 = create_vec4d(0, 9, 3);
	// v1.p = 0;
	// v2 = create_vec4d(9, 8, 0);
	// v2.p = 8;
	// v3 = create_vec4d(1, 8, 5);
	// v3.p = 3;
	// v4 = create_vec4d(0, 0, 5);
	// v4.p = 8;
	// m1 = create_mat4d(v1, v2, v3, v4);
	
	// v5 = create_vec4d(1, 2, 3);
	// v5.p = 1;
	// v6 = mult_mat4d_vec4d(m1, v5);
	// printf("%.0f, %.0f, %.0f, %.0f\n", v6.x, v6.y, v6.z, v6.p);

	// v1 = create_vec4d(1, 0, 0);
	// v1.p = 0;
	// v2 = create_vec4d(0, 1, 0);
	// v2.p = 0;
	// v3 = create_vec4d(0, 0, 1);
	// v3.p = 0;
	// v4 = create_vec4d(5, 0, 0);
	// v4.p = 1;
	// m2 = create_mat4d(v1, v2, v3, v4);

	// m3 = mult_2x_mat4d(m1, m2);

	// m2 = transpose_mat4d(m1);
	// int i = -1;
	// int j = -1;
	// while (i < 15)
	// {
	// 	while (++j < 4)
	// 		printf("%.0f ", m1.matrix[++i]);
	// 	printf("\n");
	// 	j = -1;
	// }
	// printf("equal? %d\n", is_equal_mat4d(m1, m3));

	// t_vec2d v8;
	// t_vec2d v9;
	// t_mat2d m5;

	// v8 = create_vec2d(1, 5);
	// v9 = create_vec2d(-3, 2);
	// m5 = create_mat2d(v8, v9);
	// printf("%.0f\n", determinant(m5));

	// t_vec3d	v1 = create_vec3d(1, 5, 0);
	// t_vec3d	v2 = create_vec3d(-3, 2, 7);
	// t_vec3d	v3 = create_vec3d(0, 6, -3);
	// t_mat3d	m1 = create_mat3d(v1, v2, v3);
	// t_mat2d m2 = submatrix_mat3d(m1, 1, 1);
	// int i = -1;
	// int j = -1;
	// while (i < 3)
	// {
	// 	while (++j < 2)
	// 		printf("%.0f ", m2.matrix[++i]);
	// 	printf("\n");
	// 	j = -1;
	// }

	// t_vec4d	v1 = create_vec4d(-6, 1, 1);
	// v1.p = 6;
	// t_vec4d	v2 = create_vec4d(-8, 5, 8);
	// v2.p = 6;
	// t_vec4d	v3 = create_vec4d(-1, 0, 8);
	// v3.p = 2;
	// t_vec4d	v4 = create_vec4d(-7, 1, -1);
	// v4.p = 1;
	// t_mat4d	m1 = create_mat4d(v1, v2, v3, v4);
	// t_mat3d m2 = submatrix_mat4d(m1, 3, 2);
	// int i = -1;
	// int j = -1;
	// while (i < 8)
	// {
	// 	while (++j < 3)
	// 		printf("%.0f ", m2.matrix[++i]);
	// 	printf("\n");
	// 	j = -1;
	// }

	// t_vec3d	v1 = create_vec3d(3, 5, 0);
	// t_vec3d	v2 = create_vec3d(2, -1, -7);
	// t_vec3d	v3 = create_vec3d(6, -1, 5);
	// t_mat3d	m1 = create_mat3d(v1, v2, v3);
	// printf("minor: %.0f\n", minor_mat3d(m1, 0, 0));
	// printf("cofactor: %.0f\n", cofactor_mat3d(m1, 0, 0));
	// printf("minor: %.0f\n", minor_mat3d(m1, 1, 0));
	// printf("cofactor: %.0f\n", cofactor_mat3d(m1, 1, 0));

	t_vec3d	v1 = create_vec3d(1, 2, 6);
	t_vec3d	v2 = create_vec3d(-5, 8, -4);
	t_vec3d	v3 = create_vec3d(2, 6, 4);
	t_mat3d	m1 = create_mat3d(v1, v2, v3);
	printf("det: %.0f\n", determinant_mat3d(m1));

	return (0);
}
