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

// Pattern test
	int			y;
	int			x;
	t_scene		s;
	t_light		l[1];
	t_light		l1;
	l1.position = create_point(-10, 10, -10);
	l1.color = create_color(1, 1, 1);
	l[0] = l1;
	s.lights = l;
	t_camera	cam;
	cam = set_camera(PI/2);
	cam.transform = view_transform(create_point(-25, 15, -30), create_point(1, 0, 0), create_vec4d(0, 1, 0));
	cam.inv_transform = inverse_mat4d(cam.transform);
	program.cam = cam;
	t_object	o[8];
	t_material	sphere_m;
	sphere_m.ambient.color = create_color(.1, .1, .1);
	sphere_m.diffuse = create_color(0.7, 0.7, 0.7);
	sphere_m.specular = create_color(0.3, 0.3, 0.3);
	sphere_m.shininess = 200;
	t_pattern	pat1;
	pat1.a = create_color(255, 0, 0);
	pat1.b = create_color(0, 0, 255);
	pat1.type = GRADIENT;
	pat1.p_scale = 1;
	pat1.transform = scaling_mat(10, 10, 10);
	pat1.inv_transform = inverse_mat4d(pat1.transform);
	t_pattern	pat2;
	pat2.a = scale_color(create_color(0.5, 1, 0.1), 255);
	pat2.b = create_color(186, 184, 108);
	pat2.type = STRIPED;
	pat2.p_scale = 1;
	pat2.transform = mult_n_mat4d(2, rotate_mat_z(PI/2), scaling_mat(0.5, 0.5, 0.5));
	pat2.inv_transform = inverse_mat4d(pat2.transform);
	t_pattern	pat3;
	pat3.a = create_color(255, 215, 0);
	pat3.b = create_color(113, 121, 126);
	pat3.type = RING;
	pat3.p_scale = 0.1;
	pat3.transform = scaling_mat(1, 1, 1);
	pat3.inv_transform = inverse_mat4d(pat3.transform);
	t_pattern	pat4;
	pat4.a = create_color(255, 255, 255);
	pat4.b = create_color(24, 57, 43);
	pat4.type = CHECKER;
	pat4.p_scale = 0.5;
	pat4.transform = identity_mat();
	pat4.inv_transform = inverse_mat4d(pat4.transform);
	t_pattern	pat5 = pat3;
	t_object	p;
	p.type = PLANE;
	p.material = sphere_m;
	p.material.pattern = &pat4;
	p.transform = translation_mat(0, 0, 0);
	p.inv_transform = inverse_mat4d(p.transform);
	o[0] = p;
	t_object	middle;
	middle.type = SPHERE;
	middle.center = create_point(0, 0, 0);
	middle.material = sphere_m;
	middle.material.pattern = &pat1;
	middle.material.color = scale_color(create_color(1, 0.5, 0.5), 255);
	middle.transform = mult_n_mat4d(2, scaling_mat(1, 1, 1), translation_mat(-0.5, 1, 0.5));
	middle.inv_transform = inverse_mat4d(middle.transform);
	o[1] = middle;
	t_object	right;
	right.type = SPHERE;
	right.center = create_point(0, 0, 0);
	right.material = sphere_m;
	right.material.pattern = &pat2;
	right.transform = mult_n_mat4d(2, scaling_mat(1.5, 1.5, 1.5), translation_mat(1.5, 3, -3.5));
	right.inv_transform = inverse_mat4d(right.transform);
	o[2] = right;
	t_object	left;
	left.type = SPHERE;
	left.center = create_point(0, 0, 0);
	left.material = sphere_m;
	left.material.pattern = &pat1;
	left.material.color = scale_color(create_color(1, 0.8, 0.1), 255);
	left.transform = mult_n_mat4d(2, scaling_mat(0.33, 0.33, 0.33), translation_mat(-1.5, 0.33, -0.75));
	left.inv_transform = inverse_mat4d(left.transform);
	o[3] = left;
	t_object	p2;
	p2.type = PLANE;
	p2.material = p.material;
	p2.material.pattern = &pat1;
	p2.material.color = scale_color(create_color(0.3, 0.3, 0.9), 255);
	p2.transform = mult_n_mat4d(2, rotate_mat_x(PI/2), translation_mat(0, 1.5, 2));
	p2.inv_transform = inverse_mat4d(p2.transform);
	o[4] = p2;
	t_object	p3;
	p3.type = PLANE;
	p3.material = sphere_m;
	p3.material.color = scale_color(create_color(0.3, 0.3, 0.9), 255);
	p3.material.pattern = &pat4;
	p3.transform = mult_n_mat4d(2, rotate_mat_z(PI/2), translation_mat(5, 0, 0));
	p3.inv_transform = inverse_mat4d(p3.transform);
	o[5] = p3;
	t_object	s4;
	s4.type = SPHERE;
	s4.center = create_point(0, 0, 0);
	s4.material = sphere_m;
	s4.material.pattern = &pat5;
	s4.material.pattern->transform = mult_n_mat4d(2, rotate_mat_x(PI/2), scaling_mat(0.3, 0.3, 0.3));
	s4.material.pattern->inv_transform = inverse_mat4d(s4.material.pattern->transform);
	s4.transform = mult_n_mat4d(2, scaling_mat(1.75, 1.75, 1.75), translation_mat(-10, 5, -8));
	s4.inv_transform = inverse_mat4d(s4.transform);
	o[6] = s4;
	s.objs = o;
	s.num_lights = 1;
	s.num_shapes = 7;
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
