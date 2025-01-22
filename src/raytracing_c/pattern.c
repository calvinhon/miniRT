/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:17:52 by chon              #+#    #+#             */
/*   Updated: 2025/01/20 16:40:35 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	pattern_at(t_object *o, t_point *world_point, t_pattern *pat)
{
	t_point		pat_pt;
	t_color		color;
	float		noise;

	// if (!pat)
	// 	printf("uhoh\n");
	// printf("%d\n", pat->type);
	// printf("%d: %f %f %f\n", pat->type, pat->a.r, pat->a.g, pat->a.b);
	color = pat->a;
	pat_pt = mult_mat4d_pt4d(o->inv_transform, *world_point);
	pat_pt = mult_mat4d_pt4d(pat->inv_transform, pat_pt);
	noise = 0;
	if (pat->p_scale)
	{
		noise = perlin_noise(pat_pt.x, pat_pt.y, pat_pt.z) * pat->p_scale;
		if (pat->type == GRADIENT)
			noise = fmaxf(fminf(noise, 0), -1);
		if (pat->type == CHECKER)
			noise = (0.5 + (0.5 * noise));
	}
	if ((pat->type == STRIPED && (int)floor(pat_pt.x + noise) % 2)
		|| (pat->type == RING
		&& (int)floor(sqrt(pow(pat_pt.x, 2) + pow(pat_pt.z, 2)) + noise) % 2)
		|| (pat->type == CHECKER
		&& ((int)(floor(pat_pt.x + noise) + floor(pat_pt.y + noise) + floor(pat_pt.z + noise)) % 2)))
			color = pat->b;
	else if (pat->type == GRADIENT)
		color = add_colors(2, pat->a,
			scale_color(subtract_colors(pat->b, pat->a),
				(1 + noise) * (pat_pt.x - floor(pat_pt.x))));
	return (color);
}
