/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:59:55 by chon              #+#    #+#             */
/*   Updated: 2025/01/13 10:34:40 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "colors.h"

void draw(t_mlx_vars *env)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y++ < WINDOW_H)
	{
		while (x++ < WINDOW_W)
		{
			
		}
		x = 0;
	}
	for (int i = 10000; i < 1000000; i++)
		*(unsigned int *)(env->addr + i * 4) = OLIVE;
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
