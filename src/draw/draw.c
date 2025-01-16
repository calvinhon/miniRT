/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:59:55 by chon              #+#    #+#             */
/*   Updated: 2025/01/13 15:35:51 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

<<<<<<< HEAD
void draw(t_mlx_vars *env, int x, int y, t_color c)
{
	unsigned int	color_32b;

	color_32b = plot_color(c);
=======
void draw(t_mlx_vars *env, int x, int y, t_color *c)
{
	unsigned int	color_32b;

	color_32b = plot_color(*c);
>>>>>>> 81bd0ab25fe8b8f98353709f500febd6c4c4c223
	*(unsigned int *)(env->addr + y * env->l_len + x * env->bpp_8) = color_32b;
}
