/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:59:55 by chon              #+#    #+#             */
/*   Updated: 2024/12/11 17:11:18 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "colors.h"

void	draw(t_mlx_vars *env)
{
	ft_bzero(env->addr, WINDOW_W * WINDOW_L * (env->bpp / 8));
	for (int i = 10000; i < 1000000; i++)
		*(unsigned int *)(env->addr + i * 4) = OLIVE;
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
