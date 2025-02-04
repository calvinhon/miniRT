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

void	bonus_program(t_minirt *minirt)
{
	ft_printf("Running in BONUS mode\n");
	ini_core(minirt);
	mlx_hook(minirt->win, EVENT_KEYPRESS, 1L, &record_keypress, minirt);
	mlx_hook(minirt->win, EVENT_KEYRELEASE, 1L << 1, \
		&record_keyrelease, minirt);
	mlx_hook(minirt->win, EVENT_CLOSEWINDOW, 1L >> 2, \
		&destroy_minirt, minirt);
	mlx_mouse_hook(minirt->win, &select_shape, minirt);
	mlx_loop_hook(minirt->mlx, &update_minirt, minirt);
	mlx_loop(minirt->mlx);
}

void	mandatory_program(t_minirt *minirt)
{
	int			x;
	int			y;

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
	mlx_hook(minirt->win, EVENT_CLOSEWINDOW, 1L >> 2, \
		&destroy_minirt, minirt);
	mlx_loop(minirt->mlx);
}

int	main(int ac, char **av)
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
	t_object	a;
	t_object	b;
	t_object	c;
	t_object	o[3];
	t_point		p = create_point(0, 0, -4);
	t_vec4d		dir = create_vec4d(0, 0, 1);
	t_ray		r = create_ray(&p, &dir);
	a.type = SPHERE;
	a.material.refractive = 1.5;
	a.center = create_point(0, 0, 0);
	a.transform = scaling_mat(2, 2, 2);
	a.inv_transform = inverse_mat4d(&a.transform);
	o[0] = a;
	b.type = SPHERE;
	b.material.refractive = 2.0;
	b.transform = translation_mat(0, 0, -0.25);
	b.inv_transform = inverse_mat4d(&b.transform);
	o[1] = b;
	c.type = SPHERE;
	c.material.refractive = 2.5;
	c.transform = translation_mat(0, 0, 0.25);
	c.inv_transform = inverse_mat4d(&c.transform);
	o[2] = c;
	t_scene	s;
	s.shapes = o;
	s.num_shapes = 3;
	t_itx_grp	xs = intersect(&s, &r);
	printf("count: %d\n", xs.count);
	// int i = -1;
	// while (++i < xs.count)
	// 	printf("[%d] t: %.2f\n", i, xs.arr[i].t);
	prepare_refractions(NULL, NULL, &xs);
	int i = -1;
	while (++i < xs.count)
		printf("[%d] t: %.2f n1: %.2f n2: %.2f\n", i, xs.arr[i].t, xs.arr[i].n1, xs.arr[i].n2);

	// if (bonus)
	// 	bonus_program(minirt);
	// else
	// 	mandatory_program(minirt);
	return (0);
}
