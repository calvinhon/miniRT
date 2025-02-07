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

	r_diff = fabsf((a.r) - (b.r));
	g_diff = fabsf((a.g) - (b.g));
	b_diff = fabsf((a.b) - (b.b));
	return (r_diff + g_diff + b_diff);
}
