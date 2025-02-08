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

static t_minirt	*init_minirt(void)
{
	t_minirt	*minirt;

	minirt = ft_calloc(1, sizeof(t_minirt));
	if (!minirt)
		errors(CER_MALLOC, ER_MALLOC, NULL);
	minirt->mlx = mlx_init();
	if (!minirt->mlx)
		errors(CER_MLX, ER_MLX, minirt);
	minirt->win = mlx_new_window(minirt->mlx, FRAME_W, FRAME_H, "miniRT");
	if (!make_window(minirt, FRAME_W, FRAME_H))
		errors(CER_MLX_WIN, ER_MLX_WIN, minirt);
	minirt->textures = NULL;
	minirt->selected.is_cam = true;
	minirt->selected.object = NULL;
	minirt->changed = true;
	minirt->start = true;
	minirt->scene.reflect = true;
	minirt->scene.refract = true;
	return (minirt);
}

static void	check_filename(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 3)
		errors(CER_FILE, ER_FILE, NULL);
	else if (!ft_strnstr(file + (len - 3), ".rt", len))
		errors(CER_NOT_RT, ER_NOT_RT, NULL);
	if (access(file, F_OK) != 0)
		errors(CER_NO_FILE, ER_NO_FILE, NULL);
}

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
	t_minirt	*minirt;
	bool		bonus;

	bonus = false;
	if (ac != 2 && ac != 3)
		errors(CER_AGC, ER_AGC, NULL);
	if (ac == 2)
		bonus = true;
	check_filename(av[1]);
	minirt = init_minirt();
	parse(av[1], minirt);
	if (bonus)
		bonus_program(minirt);
	else
		mandatory_program(minirt);
	return (0);
}
