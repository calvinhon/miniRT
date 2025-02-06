/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:35:32 by nth          #+#    #+#             */
/*   Updated: 2024/10/07 06:14:48 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macros.h"
#include "minirt.h"
#include "mlx.h"
#include "keys.h"

// static t_minirt	*init_minirt(void)
// {
// 	t_minirt	*minirt;

// 	minirt = ft_calloc(1, sizeof(t_minirt));
// 	if (!minirt)
// 		errors(CER_MALLOC, ER_MALLOC, NULL);
// 	minirt->mlx = mlx_init();
// 	if (!minirt->mlx)
// 		errors(CER_MLX, ER_MLX, minirt);
// 	minirt->win = mlx_new_window(minirt->mlx, FRAME_W, FRAME_H, "miniRT");
// 	if (!make_window(minirt, FRAME_W, FRAME_H))
// 		errors(CER_MLX_WIN, ER_MLX_WIN, minirt);
// 	minirt->textures = NULL;
// 	minirt->selected.is_cam = true;
// 	minirt->selected.object = NULL;
// 	minirt->changed = true;
// 	minirt->start = true;
// 	minirt->scene.fr_fl = true;
// 	return (minirt);
// }

// static void	check_filename(char *file)
// {
// 	size_t	len;

// 	len = ft_strlen(file);
// 	if (len < 3)
// 		errors(CER_FILE, ER_FILE, NULL);
// 	else if (!ft_strnstr(file + (len - 3), ".rt", len))
// 		errors(CER_NOT_RT, ER_NOT_RT, NULL);
// 	if (access(file, F_OK) != 0)
// 		errors(CER_NO_FILE, ER_NO_FILE, NULL);
// }

void bonus_program(t_minirt *minirt)
{
	ft_printf("Running in BONUS mode\n");
	ini_core(minirt);
	mlx_hook(minirt->win, EVENT_KEYPRESS, 1L, &record_keypress, minirt);
	mlx_hook(minirt->win, EVENT_KEYRELEASE, 1L << 1,
			 &record_keyrelease, minirt);
	mlx_hook(minirt->win, EVENT_CLOSEWINDOW, 1L >> 2,
			 &destroy_minirt, minirt);
	mlx_mouse_hook(minirt->win, &select_shape, minirt);
	mlx_loop_hook(minirt->mlx, &update_minirt, minirt);
	mlx_loop(minirt->mlx);
}

void mandatory_program(t_minirt *minirt)
{
	int x;
	int y;

	ft_printf("Running in MANDATORY mode\n");
	x = -1;
	y = -1;
	while (++y < minirt->cam.vsize - 1)
	{
		while (++x < minirt->cam.hsize - 1)
			render_pixel(minirt, x, y);
		x = -1;
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->frame.ptr, 0, 0);
	mlx_hook(minirt->win, EVENT_CLOSEWINDOW, 1L >> 2,
			 &destroy_minirt, minirt);
	mlx_loop(minirt->mlx);
}

int main(int ac, char **av)
{
	// t_minirt	*minirt;
	// bool		bonus;

	// bonus = false;
	// if (ac != 2 && ac != 3)
	// 	errors(CER_AGC, ER_AGC, NULL);
	// if (ac == 3)
	// 	bonus = true;
	// check_filename(av[1]);
	// minirt = init_minirt();
	// parse(av[1], minirt);

	// Refraction test
	(void)ac;
	(void)av;
	t_light	l1;
	l1.type = POINT_LIGHT;
	l1.intensity = create_color(255, 255, 255);
	l1.pos = create_point(0, 0, 0);
	t_light	l[1];
	l[0] = l1;
	t_object a;
	t_object b;
	// t_object c;
	t_object o[2];
	t_point p = create_point(0, 0, 0.1);
	t_vec4d dir = create_vec4d(0, 1, 0);
	t_ray r = create_ray(&p, &dir);
	a.type = SPHERE;
	a.material.ambient_s = 1.0;
	a.material.reflective = 0;
	a.material.transparency = 0;
	a.material.refractive = 0;
	a.material.diffuse_s = 0.7;
	a.material.specular_s = 0.3;
	a.material.shininess = 200;
	a.material.color = create_color(0, 255, 0);
	a.material.pattern = NULL;
	a.center = create_point(0, 0, 0);
	a.transform = identity_mat();
	a.inv_transform = inverse_mat4d(&a.transform);
	o[0] = a;
	b.type = SPHERE;
	b.material.ambient_s = 1.0;
	b.material.reflective = 0;
	b.material.transparency = 1.0;
	b.material.refractive = 1.5;
	b.material.color = create_color(255, 255, 255);
	b.material.pattern = NULL;
	b.center = create_point(0, 0, 0);
	b.transform = scaling_mat(0.5, 0.5, 0.5);
	b.inv_transform = inverse_mat4d(&b.transform);
	o[1] = b;
	// c.type = SPHERE;
	// c.material.refractive = 2.5;
	// c.transform = translation_mat(0, 0, 0.25);
	// c.inv_transform = inverse_mat4d(&c.transform);
	// o[2] = c;
	t_scene s;
	s.num_lights = 1;
	s.lights = l;
	s.shapes = o;
	s.num_shapes = 2;
	s.ambiance = create_color(255, 255, 255);
	t_itx_grp xs = intersect(&s, &r);
	// printf("count: %d\n", xs.count);
	// // int i = -1;
	// // while (++i < xs.count)
	// // 	printf("[%d] t: %.2f\n", i, xs.arr[i].t);
	// prepare_refractions(NULL, NULL, &xs);
	t_itx	*itx = get_hit(&xs);
	t_comps	comps = prepare_computations(itx, &r, &xs);
	// printf("comps t: %.2f\n", comps.t);
	// int i = -1;
	// while (++i < xs.count)
	// 	printf("[%d] t: %.2f n1: %.2f n2: %.2f\n", i, xs.arr[i].t, xs.arr[i].n1, xs.arr[i].n2);
	printf("t: %.2f r: %.2f\n", xs.arr[2].t, xs.arr[2].obj->material.refractive);
	// printf("point: %.5f %.5f %.5f\n", comps.p.x, comps.p.y, comps.p.z);
	// printf("under point: %.5f %.5f %.5f\n", comps.under_point.x, comps.under_point.y, comps.under_point.z);
	t_color	color = refracted_color(&s, &xs.arr[2], &comps, 5);
	printf("refracted color: %.5f %.5f %.5f\n", color.r, color.g, color.b);

	// if (bonus)
	// 	bonus_program(minirt);
	// else
	// 	mandatory_program(minirt);
	return (0);
}
