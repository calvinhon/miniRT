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

	t_vec4d v1;
	t_vec4d v2;
	t_vec4d v3;
	t_vec4d v4;
	// t_vec4d v5;
	// t_vec4d v6;
	t_mat4d m1;
	t_mat4d m2;
	t_mat4d m3;

	v1 = create_vector(1, 2, 3);
	v1.p = 4;
	v2 = create_vector(2, 4, 4);
	v2.p = 2;
	v3 = create_vector(8, 6, 4);
	v3.p = 1;
	v4 = create_vector(0, 0, 0);
	v4.p = 1;
	m1 = create_mat4d(v1, v2, v3, v4);
	
	// v5 = create_vector(1, 2, 3);
	// v5.p = 1;
	// v6 = mult_mat4d_vec4d(m1, v5);
	// printf("%.0f, %.0f, %.0f, %.0f\n", v6.x, v6.y, v6.z, v6.p);

	v1 = create_vector(1, 0, 0);
	v1.p = 0;
	v2 = create_vector(0, 1, 0);
	v2.p = 0;
	v3 = create_vector(0, 0, 1);
	v3.p = 0;
	v4 = create_vector(5, 0, 0);
	v4.p = 1;
	m2 = create_mat4d(v1, v2, v3, v4);

	m3 = mult_2x_mat4d(m1, m2);
	int i = -1;
	while (++i < 16)
		printf("%d: %.0f\n", i, m3.matrix[i]);

	m2 = transpose_mat4d(m3);
	i = -1;
	while (++i < 16)
		printf("%d: %.0f\n", i, m2.matrix[i]);
	// printf("equal? %d\n", is_equal_mat4d(m1, m3));


	return (0);
}
