/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_h.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:44:06 by chon              #+#    #+#             */
/*   Updated: 2024/12/19 01:21:02 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minirt.h"
#include "../include/parsing.h"

int	main(int ac, char **av)
{
	t_minirt	*minirt;
	void		*mlx_ptr;
	void		*win_ptr;

	if (ac != 2)
		errors(ER_AGC, NULL);
	check_filename(av[1]);
	minirt = new_minirt();
	parse(minirt, av[1]);
	ini_all(minirt);
	// ini_graphic
	// ini_threads
	// ini_viewport
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		errors(ER_MLX, minirt);
	minirt->graphic.mlx = mlx_ptr;
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "MiniRT");
	if (!win_ptr)
		errors(ER_MLX, minirt);
	minirt->graphic.win = win_ptr;
	mlx_key_hook(win_ptr, handle_keypress , minirt);
	mlx_loop_hook(win_ptr, update_draw, minirt);
	mlx_hook(win_ptr, 17, 0, close_window, minirt);
	mlx_loop(mlx_ptr);
	return (OK);
}
