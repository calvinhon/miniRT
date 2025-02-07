/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:17:52 by chon              #+#    #+#             */
/*   Updated: 2025/01/30 13:57:32 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "colors.h"

t_color	add_noise_to_color(t_color color, float noise)
{
	color.r += noise;
	color.g += noise;
	color.b += noise;
	return (color);
}

t_color	calculate_color(t_pattern *pat, t_point *pat_pt, float noise)
{
	t_color	color;

	color = pat->a;

	if ((pat->type == STRIPED && (int)floorf(pat_pt->x) % 2) || \
		(pat->type == RING && (int)floorf(sqrtf(pat_pt->x * pat_pt->x + \
		pat_pt->z * pat_pt->z)) % 2) || \
		(pat->type == CHECKER && ((int)(floorf(pat_pt->x) + \
		floorf(pat_pt->y) + floorf(pat_pt->z)) % 2)))
		color = pat->b;
	if (pat->type == STRIPED || pat->type == RING || pat->type == CHECKER)
		color = add_noise_to_color(color, noise);
	else if (pat->type == GRADIENT)
	{
		color = subtract_colors(&pat->b, &pat->a);
		color = scale_color(&color, (1 + noise) * (pat_pt->x - \
		floorf(pat_pt->x)));
		color = add_colors(2, &pat->a, &color);
	}
	return (color);
}

t_color	pattern_at(t_object *o, t_point *world_point, t_pattern *pat)
{
	t_point	pat_pt;
	float	noise;

	noise = 0;
	pat_pt = mult_mat4d_pt4d(&o->inv_transform, world_point);
	pat_pt = mult_mat4d_pt4d(&pat->inv_transform, &pat_pt);
	if (pat && pat->p_scale)
	{
		noise = perlin_noise(pat_pt.x, pat_pt.y, pat_pt.z) * pat->p_scale;
		if (pat->type == GRADIENT)
			noise = fmaxf(fminf(noise, 0), -1);
		if (pat->type == CHECKER)
			noise = (0.5 + (0.5 * noise));
	}
	return (calculate_color(pat, &pat_pt, noise));
}
