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
#include "miniRT.h"
#include "mlx.h"
#include "keys.h"

void	errors(int err_code, char *err_ms, void *ptr)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)ptr;
	if (minirt)
		free_minirt(minirt);
	ft_putstr_fd(err_ms, 2);
	exit(err_code);
}

int	destroy_minirt(t_minirt *minirt)
{
	free_minirt(minirt);
	exit(0);
	return (0);
}

t_minirt	*ini_minirt(void)
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
	minirt->selected = (struct s_select){.is_cam = true, .object = NULL};
	return (minirt);
}

void	check_filename(char *file)
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

int	main(int ac, char **av)
{
	t_minirt	*minirt;

	if (ac != 2)
		errors(CER_AGC, ER_AGC, NULL);
	check_filename(av[1]);
	minirt = ini_minirt();
	parse(av[1], minirt);
	ini_core(minirt);
	mlx_hook(minirt->win, EVENT_KEYPRESS, 1L, &record_keypress, minirt);
	mlx_hook(minirt->win, EVENT_KEYRELEASE, 1L << 1, \
		&record_keyrelease, minirt);
	mlx_hook(minirt->win, EVENT_CLOSEWINDOW, 1L >> 2, \
		&destroy_minirt, minirt);
	mlx_mouse_hook(minirt->win, &select_shape, minirt);
	mlx_loop_hook(minirt->mlx, &update_minirt, minirt);
	mlx_loop(minirt->mlx);
	return (0);
}
