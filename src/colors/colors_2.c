/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:16:33 by chon              #+#    #+#             */
/*   Updated: 2025/01/29 12:54:28 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

t_color	normalize_color(t_color c)
{
	float	max;

	max = fmaxf(fmaxf(c.r, c.g), c.b);
	return (create_color(c.r * 255 / max, c.g * 255 / max, c.b * 255 / max));
}

unsigned int plot_color(t_color *c)
{
	if (c->r > 255)
		c->r = 255;
	if (c->g > 255)
		c->g = 255;
	if (c->b > 255)
		c->b = 255;
	// if (c.r > 0)
	// 	printf("c_color: %.2f %.2f %.2f\n", c.r, c.g, c.b);
	return ((unsigned int)c->r << 16 | (unsigned int)c->g << 8 | (unsigned int)c->b);
}
