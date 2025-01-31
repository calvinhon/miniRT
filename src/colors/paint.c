/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 01:37:10 by nth          #+#    #+#             */
/*   Updated: 2024/10/07 02:43:49 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "minirt.h"
#include "macros.h"

int cdiff(t_color a, t_color b)
{
	int r_diff;
	int g_diff;
	int b_diff;

	r_diff = fabs((a.r) - (b.r));
	g_diff = fabs((a.g) - (b.g));
	b_diff = fabs((a.b) - (b.b));
	return (r_diff + g_diff + b_diff);
}

void clamp_color(t_color *color)
{
	if (color->r > 1)
		color->r = 1;
	else if (color->r < 0)
		color->r = 0;
	if (color->g > 1)
		color->g = 1;
	else if (color->g < 0)
		color->g = 0;
	if (color->b > 1)
		color->b = 1;
	else if (color->b < 0)
		color->b = 0;
}

//uint32_t convert_color32(const t_color *_color)
//{
//	uint32_t r;
//	uint32_t g;
//	uint32_t b;
//	uint32_t color_value;
//	t_color color;

//	color = *_color;
//	clamp_color(&color);
//	r = (uint32_t)(color.r);
//	g = (uint32_t)(color.g);
//	b = (uint32_t)(color.b);
//	color_value = 0xFF000000 * (OS_MACOS == 0);
//	return (color_value | r << 16 | g << 8 | b);
//}
