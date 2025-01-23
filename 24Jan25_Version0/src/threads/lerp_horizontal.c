/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:11:01 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 18:55:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

static void	fill_in_horizontal(t_core const *data, int x, int y)
{
	t_color		c_i;
	t_color		c_f;
	t_color		temp;

	c_i = fetch_pixel_color(&data->minirt->frame, x - 1, y);
	c_f = fetch_pixel_color(&data->minirt->frame, x + STEP_SKIP - 1, y);
	if (cdiff(c_i, c_f) > INTP_THRES)
	{
		rt_render_pixel(data->minirt, x, y);
		rt_render_pixel(data->minirt, x + 1, y);
	}
	else
	{
		temp = lerp_colors(&c_i, &c_f, 2.0f / 3.0f);
		put_pixel(&data->minirt->frame, x, y, &temp);
		temp = lerp_colors(&c_i, &c_f, 1.0f / 3.0f);
		put_pixel(&data->minirt->frame, x + 1, y, &temp);
	}
}

static void	check_horizontal_fill(t_core const *data, int x, int y)
{
	t_minirt	*minirt;
	t_camera	*cam;
	t_color		temp;

	minirt = data->minirt;
	cam = &minirt->cam;
	if (x + (STEP_SKIP - 1) < cam->hsize)
		fill_in_horizontal(data, x, y);
	else
	{
		temp = fetch_pixel_color(&minirt->frame, x - 1, y);
		if (x < cam->hsize)
			put_pixel(&minirt->frame, x, y, &temp);
		temp = fetch_pixel_color(&minirt->frame, x, y);
		if (x + 1 < cam->hsize)
			put_pixel(&minirt->frame, x + 1, y, &temp);
	}
}

void	interpolate_horizontal(t_core const *data)
{
	t_minirt	*minirt;
	t_camera	*cam;
	int			x;
	int			y;
	int			yend;

	minirt = data->minirt;
	cam = &minirt->cam;
	y = data->y;
	yend = data->yend;
	while (y < yend)
	{
		x = 1;
		while (x < cam->hsize)
		{
			check_horizontal_fill(data, x, y);
			x += STEP_SKIP;
		}
		y++;
	}
}
