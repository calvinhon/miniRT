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

#include "miniRT.h"

int init_frame(t_frame *frame)
{
	frame->mlx = mlx_init();
	if (!frame->mlx)
	{
		printf("Error initializing mlx\n");
		return (1);
	}
	frame->win = mlx_new_window(frame->mlx, WINDOW_W, WINDOW_H, "Rayineers' miniRT");
	frame->img = mlx_new_image(frame->mlx, WINDOW_W, WINDOW_H);
	frame->addr = mlx_get_data_addr(frame->img, &frame->bpp, &frame->l_len, &frame->end);
	frame->bpp_8 = frame->bpp / 8;
	if (!frame->win || !frame->img || !frame->addr)
		return (1);
	set_controls(frame);
	return (0);
}

int main(int ac, char **av)
{
	t_minirt program;
	t_frame frame;

	if (ac != 1) // change to 2
	{
		printf("Input scenes/<filename>.rt as 2nd argument\n");
		return (1);
	}
	(void)av;
	if (init_frame(&program.frame))
		return (1);

// Cylinder test
	int y;
	int x;
	t_scene s;
	t_light l[1];
	t_light l1;
	l1.position = create_point(-5, 10, -5);
	l1.color = create_color(255, 255, 255);
	l[0] = l1;
	s.lights = l;
	t_camera cam;
	cam = set_camera(PI / 3);
	cam.fromform = view_transform(create_point(-13, 10, -20), create_point(0, 1, 0), create_vec4d(0, 1, 0));
	cam.inv_transform = inverse_mat4d(cam.fromform);
	program.cam = cam;
	t_object o[8];
	t_material sphere_m;
	sphere_m.ambient_s = 0.1;
	sphere_m.diffuse_s = 0.7;
	sphere_m.specular_s = 0.3;
	sphere_m.shininess = 200;
	sphere_m.color = create_color(125, 125, 125);
	t_pattern pat1;
	pat1.a = create_color(255, 0, 0);
	pat1.b = create_color(0, 0, 255);
	pat1.type = GRADIENT;
	pat1.p_scale = 0;
	pat1.transform = scaling_mat(10, 10, 10);
	pat1.inv_transform = inverse_mat4d(pat1.transform);
	t_pattern pat2;
	pat2.a = scale_color(create_color(0.5, 1, 0.1), 255);
	pat2.b = create_color(186, 184, 108);
	pat2.type = STRIPED;
	pat2.p_scale = 0;
	pat2.transform = mult_n_mat4d(2, rotate_mat_z(PI / 2), scaling_mat(0.5, 0.5, 0.5));
	pat2.inv_transform = inverse_mat4d(pat2.transform);
	t_pattern pat3;
	pat3.a = create_color(255, 215, 0);
	pat3.b = create_color(113, 121, 126);
	pat3.type = RING;
	pat3.p_scale = 0;
	pat3.transform = scaling_mat(1, 1, 1);
	pat3.inv_transform = inverse_mat4d(pat3.transform);
	t_pattern pat4;
	pat4.a = create_color(255, 255, 255);
	pat4.b = create_color(24, 57, 43);
	pat4.type = CHECKER;
	pat4.p_scale = 0;
	pat4.transform = identity_mat();
	pat4.inv_transform = inverse_mat4d(pat4.transform);
	// t_pattern pat5 = pat3;
	t_object p;
	p.type = PLANE;
	p.material = sphere_m;
	p.material.reflect_s = 0;
	p.material.pattern = &pat4;
	p.transform = translation_mat(0, 0, 0);
	p.inv_transform = inverse_mat4d(p.transform);
	o[0] = p;
	t_object middle;
	middle.type = SPHERE;
	middle.center = create_point(0, 0, 0);
	middle.material = sphere_m;
	middle.material.reflect_s = 0;
	middle.material.pattern = &pat1;
	middle.material.color = scale_color(create_color(1, 0.5, 0.5), 255);
	middle.transform = mult_n_mat4d(2, scaling_mat(1, 1, 1), translation_mat(-0.5, 1, 0.5));
	middle.inv_transform = inverse_mat4d(middle.transform);
	o[1] = middle;
	t_object right;
	right.type = SPHERE;
	right.center = create_point(0, 0, 0);
	right.material = sphere_m;
	right.material.color = create_color(255, 0, 0);
	right.material.reflect_s = 1;
	right.material.pattern = NULL;
	right.transform = mult_n_mat4d(2, scaling_mat(1.5, 1.5, 1.5), translation_mat(-8, 2, -5));
	right.inv_transform = inverse_mat4d(right.transform);
	o[2] = right;
	t_object left;
	left.type = SPHERE;
	left.center = create_point(0, 0, 0);
	left.material = sphere_m;
	left.material.reflect_s = 1;
	left.material.pattern = NULL;
	left.material.color = scale_color(create_color(1, 0.8, 0.1), 255);
	left.transform = mult_n_mat4d(2, scaling_mat(0.33, 0.33, 0.33), translation_mat(-1.5, 0.33, -0.75));
	left.inv_transform = inverse_mat4d(left.transform);
	o[3] = left;
	t_object p2;
	p2.type = PLANE;
	p2.material = p.material;
	p2.material.pattern = NULL;
	p2.material.color = scale_color(create_color(1, 1, 1), 255);
	p2.material.reflect_s = 0;
	p2.transform = mult_n_mat4d(2, rotate_mat_x(PI / 2), translation_mat(0, 1.5, 2));
	p2.inv_transform = inverse_mat4d(p2.transform);
	o[4] = p2;
	t_object p3;
	p3.type = PLANE;
	p3.material = sphere_m;
	p3.material.color = scale_color(create_color(0.3, 0.3, 0.9), 255);
	p3.material.reflect_s = 0;
	p3.material.pattern = &pat4;
	p3.transform = mult_n_mat4d(2, rotate_mat_z(PI / 2), translation_mat(5, 0, 0));
	p3.inv_transform = inverse_mat4d(p3.transform);
	o[5] = p3;
	t_object s4;
	s4.type = SPHERE;
	s4.center = create_point(0, 0, 0);
	s4.material = sphere_m;
	s4.material.pattern = NULL;
	// s4.material.pattern = &pat3;
	// s4.material.pattern->transform = mult_n_mat4d(2, rotate_mat_x(PI / 2), scaling_mat(0.3, 0.3, 0.3));
	// s4.material.pattern->inv_transform = inverse_mat4d(s4.material.pattern->transform);
	s4.material.color = create_color(0, 255, 0);
	s4.material.reflect_s = 1;
	s4.transform = mult_n_mat4d(2, scaling_mat(1.75, 1.75, 1.75), translation_mat(4, 3, -10));
	s4.inv_transform = inverse_mat4d(s4.transform);
	o[6] = s4;
	t_object c1;
	c1.type = CYLINDER;
	c1.center = create_point(0, 0, 0);
	c1.specs.t_cyl.min_y = 1;
	c1.specs.t_cyl.max_y = 5;
	c1.specs.t_cyl.closed = 1;
	c1.material = sphere_m;
	c1.material.pattern = NULL;
	// c1.material.pattern->p_scale = 0;
	c1.material.color = create_color(0, 168, 107);
	c1.material.reflect_s = 1;
	c1.transform = identity_mat();
	c1.transform = mult_n_mat4d(4, rotate_mat_z(PI/5), rotate_mat_x(-PI/7), scaling_mat(1, 1, 1), translation_mat(0, 5, -5));
	c1.inv_transform = inverse_mat4d(c1.transform);
	o[7] = c1;
	s.objs = o;
	s.num_lights = 1;
	s.num_shapes = 8;
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

	// t_point point = create_point(1, 2, 0.5);
	// // t_vec4d	direction = create_vec4d(0, 1, 1);
	// // direction = normalize(direction);
	// // t_ray	r = create_ray(&point, &direction);
	// // t_itx_grp	xs;
	// // intersect_cylinder(&r, &c1, &xs);
	// // printf("%d\n", xs.count);
	// t_vec4d	normal = cylinder_normal_at(&c1, &point);
	// printf("%.2f, %.2f, %.2f\n", normal.x, normal.y, normal.z);

	frame = program.frame;
	mlx_put_image_to_window(frame.mlx, frame.win, frame.img, 0, 0);
	mlx_loop(frame.mlx);
	return (0);
}
