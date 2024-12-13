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

#include "../include/minirt.h"

void	errors(int err_code, t_minirt *minirt)
{
	close_minirt(minirt);
	if (err_code == ER_AGC)
		ft_putstr_fd(ER_USAGE, 2);
	else if (err_code == ER_FILE)
		ft_putstr_fd(ER_NOT_RT, 2);
	else if (err_code == ER_MOR)
		ft_putstr_fd(ER_NOT_RT, 2);
	else
		ft_putstr_fd("Other Errors \n", 2);
	exit(err_code);
}

// can delete below as I have in controls directory
int handle_keypress(int key, t_minirt *minirt)
{
	if (key == KEY_LEFT || key == KEY_A)
		minirt->camera.origin.x -= 10;
	else if (key == KEY_RIGHT || key == KEY_D)
		minirt->camera.origin.x += 10;
	else if (key == KEY_UP || key == KEY_W)
		minirt->camera.origin.y += 10;
	else if (key == KEY_DOWN || key == KEY_S)
		minirt->camera.origin.y -= 10;
    else if (key == KEY_C)
		minirt->camera.origin.z -= 10;
	else if (key == KEY_V)
		minirt->camera.origin.z += 10;
	else if (key == KEY_ESC || key == KEY_Q)
		close_window(minirt, "Window Closed\n");
    ray_trace(minirt);
	return (0);
}

void	free_minirt(t_minirt *minirt)
{
	if (!minirt)
		return ;
	if (minirt->win)
		mlx_destroy_window(minirt->mlx, minirt->win);
	if (minirt->img)
		mlx_destroy_iamge(minirt->mlx, minirt->img);	
	free_mlx(minirt->mlx);
	free(minirt);
	minirt = NULL;
	
  
}
int	close_window(t_minirt *minirt, char *s)
{
	if (*s == 'c')
		s = "Window Closed\n";
	ft_printf("%s", s);
	mlx_clear_window(minirt->mlx, minirt->win);
	mlx_destroy_window(minirt->mlx, minirt->win);
	free_minirt(minirt);
	exit(OK);
    return OK;
}


int main(int ac, char **av)
{
	t_minirt	*minirt;

	if (ac != 2)
		errors(ER_AGC, NULL);
	check_file(av[1]);
	minirt = new_minirt();
	parse(minirt, av[1]);
	ini_all(minirt);
	ray_trace(minirt);
    mlx_key_hook(minirt->win, handle_keypress, minirt);
	mlx_hook(minirt->win, 17, 0, close_window, minirt); //17, 0 = DestroyNotify, StructureNotifyMask,
    mlx_loop(minirt->mlx);
    free_minirt(minirt);
    return (OK);
}