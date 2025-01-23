/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:16:04 by nth          #+#    #+#             */
/*   Updated: 2024/11/18 12:16:04 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "macros.h"

void	add_color(t_color *target, const t_color *c1, const t_color *c2)
{
	float	r;
	float	b;
	float	g;

	r = c1->r + c2->r;
	g = c1->g + c2->g;
	b = c1->b + c2->b;
	target->v = vec4s_re((OS_MACOS == 0), r, g, b);
}

void	sub_color(t_color *target, const t_color *c1, const t_color *c2)
{
	float	r;
	float	b;
	float	g;

	r = c1->r - c2->r;
	g = c1->g - c2->g;
	b = c1->b - c2->b;
	target->v = vec4s_re((OS_MACOS == 0), r, g, b);
}

void	blend_color(t_color *target, const t_color *c1, const t_color *c2)
{
	float	r;
	float	b;
	float	g;

	r = c1->r * c2->r;
	g = c1->g * c2->g;
	b = c1->b * c2->b;
	target->v = vec4s_re((OS_MACOS == 0), r, g, b);
}

void	scale_color(t_color *target, const t_color *c, float scalar)
{
	float	r;
	float	b;
	float	g;

	r = c->r * scalar;
	g = c->g * scalar;
	b = c->b * scalar;
	target->v = vec4s_re((OS_MACOS == 0), r, g, b);
}
