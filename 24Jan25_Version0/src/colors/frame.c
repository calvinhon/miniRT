/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 01:26:02 by nth          #+#    #+#             */
/*   Updated: 2024/10/07 02:23:51 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "colors.h"
#include "mlx.h"
#include "macros.h"

bool	make_window(t_minirt *minirt, int width, int height)
{
	minirt->frame.ptr = mlx_new_image(minirt->mlx, width, height);
	if (!minirt->frame.ptr)
		return (false);
	minirt->frame.addr = mlx_get_data_addr(	minirt->frame.ptr, &minirt->frame.bpp,
 &minirt->frame.line_length, &minirt->frame.endian);
	minirt->frame.bpp_8 = minirt->frame.bpp / 8;
	return (true);
}

void	put_pixel(t_frame *frame, int x, int y, const t_color *color)
{
	char	*dst;

	dst = frame->addr + (y * frame->line_length + x * frame->bpp_8);
	*(uint32_t *)dst = convert_color32(color);
}

t_color	lerp_colors(const t_color *a, const t_color *b, float t)
{
	t_color	ret;

	ret.r = (b->r * t) + (a->r * (1.f - t));
	ret.g = (b->g * t) + (a->g * (1.f - t));
	ret.b = (b->b * t) + (a->b * (1.f - t));
	ret.a = 1;
	if (OS_MACOS)
		ret.a = 0;
	return (ret);
}

t_color	fetch_pixel_color(const t_frame *frame, int x, int y)
{
	char		*src;
	uint32_t	color_value;
	t_color		ret;

	src = frame->addr + (y * frame->line_length + x * frame->bpp_8);
	color_value = *(uint32_t *)src;
	ret.r = (color_value >> 16) & 0xFF;
	ret.g = (color_value >> 8) & 0xFF;
	ret.b = color_value & 0xFF;
	ret.a = 1;
	if (OS_MACOS)
		ret.a = 0;
	ret.r = ret.r / 255.999;
	ret.g = ret.g / 255.999;
	ret.b = ret.b / 255.999;
	return (ret);
}
