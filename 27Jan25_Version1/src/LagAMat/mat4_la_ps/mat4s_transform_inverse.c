/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4s_transform_inverse.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 07:03:08 by nth               #+#    #+#             */
/*   Updated: 2024/11/02 09:37:45 by nth              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

static void	transpose_and_scale_rotation(const t_mat4s rot, \
	t_mat4s *ret, const t_vec4s rcps)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		ret->a[i][0] = rot.a[0][i] * rcps.a[0];
		ret->a[i][1] = rot.a[1][i] * rcps.a[1];
		ret->a[i][2] = rot.a[2][i] * rcps.a[2];
		ret->a[i][3] = 0.f;
	}
	ret->a[3][0] = 0.f;
	ret->a[3][1] = 0.f;
	ret->a[3][2] = 0.f;
	ret->a[3][3] = 1.f;
}

t_mat4s	get_inv_tranform_mat4s(const t_mat4s rot, const t_vec4s s, \
	const t_vec4s t)
{
	t_mat4s	ret;
	t_vec4s	rcps;
	t_vec4s	tinv;

	rcps = vec4s_re(1.f / s.a[0], 1.f / s.a[1], 1.f / s.a[2], 1.f);
	tinv = vec4s_re(-t.a[0], -t.a[1], -t.a[2], -t.a[3]);
	transpose_and_scale_rotation(rot, &ret, rcps);
	ret.a[0][3] = ret.a[0][0] * tinv.a[0] + ret.a[0][1] * tinv.a[1] \
		+ ret.a[0][2] * tinv.a[2];
	ret.a[1][3] = ret.a[1][0] * tinv.a[0] + ret.a[1][1] * tinv.a[1] \
		+ ret.a[1][2] * tinv.a[2];
	ret.a[2][3] = ret.a[2][0] * tinv.a[0] + ret.a[2][1] * tinv.a[1] \
		+ ret.a[2][2] * tinv.a[2];
	return (ret);
}
