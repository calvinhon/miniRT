/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:55:07 by chon              #+#    #+#             */
/*   Updated: 2024/12/11 15:55:07 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

t_color create_color(float r, float g, float b)
{
	t_color c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color add_colors(int num_of_colors, ...)
{
	t_color c;
	int i;
	t_color c_arg;
	va_list args;

	va_start(args, num_of_colors);
	i = -1;
	c = create_color(0, 0, 0);
	while (++i < num_of_colors)
	{
		c_arg = va_arg(args, t_color);
		c.r += c_arg.r;
		c.g += c_arg.g;
		c.b += c_arg.b;
	}
	va_end(args);
	return (create_color(c.r, c.g, c.b));
}

t_color subtract_colors(t_color c1, t_color c2)
{
	return (create_color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b));
}

t_color scale_color(t_color c, float scale)
{
	return (create_color(c.r * scale, c.g * scale, c.b * scale));
}

t_color mult_colors(t_color c1, t_color c2)
{
	return (create_color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b));
}

unsigned int plot_color(t_color c)
{
	if (c.r > 255)
		c.r = 255;
	if (c.g > 255)
		c.g = 255;
	if (c.b > 255)
		c.b = 255;
	return ((unsigned int)c.r << 16 | (unsigned int)c.g << 8 | (unsigned int)c.b);
}