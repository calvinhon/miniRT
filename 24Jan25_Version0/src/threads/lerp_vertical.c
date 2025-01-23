/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:35:38 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 18:47:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

static void	fill_in_vertically(t_core const *data, int x, int y)
{
	t_color		c_i;
	t_color		c_f;
	t_color		temp;

	c_i = fetch_pixel_color(&data->minirt->frame, x, y - 1);
	if (y + STEP_SKIP - 1 >= data->minirt->cam.vsize)
		c_f = fetch_pixel_color(&data->minirt->frame, x,
				data->minirt->cam.vsize - 1);
	else
		c_f = fetch_pixel_color(&data->minirt->frame, x,
				y + STEP_SKIP - 1);
	if (cdiff(c_i, c_f) > INTP_THRES)
	{
		rt_render_pixel(data->minirt, x, y);
		rt_render_pixel(data->minirt, x, y + 1);
	}
	else
	{
		temp = lerp_colors(&c_i, &c_f, 2.0f / 3.0f);
		put_pixel(&data->minirt->frame, x, y, &temp);
		temp = lerp_colors(&c_i, &c_f, 1.0f / 3.0f);
		put_pixel(&data->minirt->frame, x, y + 1, &temp);
	}
}

static void	check_vertical_fill(t_core const *data, int x, int y)
{
	t_minirt		*minirt;
	t_camera		*cam;
	t_color			temp;

	minirt = data->minirt;
	cam = &minirt->cam;
	if (y + (STEP_SKIP - 1) < cam->vsize)
		fill_in_vertically(data, x, y);
	else
	{
		temp = fetch_pixel_color(&minirt->frame, x, y - 1);
		if (y < cam->vsize)
			put_pixel(&minirt->frame, x, y, &temp);
		temp = fetch_pixel_color(&minirt->frame, x, y);
		if (y + 1 < cam->vsize)
			put_pixel(&minirt->frame, x, y + 1, &temp);
	}
}

void	interpolate_vertical(t_core const *data)
{
	t_minirt		*minirt;
	t_camera		*cam;
	int				x;
	int				y;
	int				yend;

	minirt = data->minirt;
	cam = &minirt->cam;
	yend = data->yend;
	y = data->y + 1;
	while (y < yend)
	{
		x = 1;
		while (x < cam->hsize)
		{
			check_vertical_fill(data, x, y);
			x++;
		}
		y += STEP_SKIP;
	}
}
