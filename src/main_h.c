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

int	main(int ac, char **av)
{
	t_minirt	*minirt;

	if (ac != 2)
		errors(ER_AGC, NULL);
	check_filename(av[1]);
	minirt = new_minirt();
	parse(minirt, av[1]);
	//ini_graphic(minirt);
	//ini_threads(minirt);
    // Initialize minirt, mlx, window, and image
	
    minirt.mlx = mlx_init();
    minirt.win = mlx_new_window(minirt.mlx, minirt.width, minirt.height, "MiniRT");
    minirt.img = mlx_new_image(minirt.mlx, minirt.width, minirt.height);

    mlx_key_hook(minirt.win, key_press, &minirt);
    mlx_hook(minirt.win, 6, 0, mouse_move, &minirt); // 6 is the event code for mouse move

    ray_trac_loop(&minirt);
	free_minirt(minirt);
	return (OK);
}
