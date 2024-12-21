

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:47:33 by marvin            #+#    #+#             */
/*   Updated: 2024/12/11 17:47:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_minirt(t_minirt *minirt)
{
	if (!minirt)
		return ;
	if (minirt->graphic.win)
		mlx_destroy_window(minirt->graphic.mlx, minirt->graphic.win);
	if (minirt->graphic.img)
		mlx_destroy_image(minirt->graphic.mlx, minirt->graphic.img);
	free_mlx(minirt->graphic.mlx);
	free_scene(minirt->scene);
	free_threads(minirt->comp_units);
	free(minirt);
	minirt = NULL;
}

int	close_window(t_minirt *minirt, char *s)
{
	if (*s == 'c')
		s = "Window Closed\n";
	ft_printf("%s", s);
	mlx_clear_window(minirt->graphic.mlx, minirt->graphic.win);
	mlx_destroy_window(minirt->graphic.mlx, minirt->graphic.win);
	free_minirt(minirt);
	exit(OK);
	return (OK);
}