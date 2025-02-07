/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4d_transform_inverse.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 07:03:08 by nth               #+#    #+#             */
/*   Updated: 2024/11/02 09:37:45 by nth              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_math.h"

static void	transpose_and_scale_rotation(const t_mat4d rot, \
    t_mat4d *ret, const t_point rcps)
{
    int	i;

    i = -1;
    while (++i < 3)
    {
        ret->matrix[4 * i] = rot.matrix[i] * rcps.x;
        ret->matrix[4 * i + 1] = rot.matrix[4 + i] * rcps.y;
        ret->matrix[4 * i + 2] = rot.matrix[8 + i] * rcps.z;
        ret->matrix[4 * i + 3] = 0.f;
    }
    ret->matrix[12] = 0.f;
    ret->matrix[13] = 0.f;
    ret->matrix[14] = 0.f;
    ret->matrix[15] = 1.f;
}
t_mat4d	get_inv_tranform_mat4d(const t_mat4d rot, const t_vec4d s, \
	const t_point t)
{
	t_mat4d	ret;
	t_point	rcps;
	t_vec4d	tinv;

	rcps = create_point(1.f / s.x, 1.f / s.y, 1.f / s.z);
	tinv = create_vec4d(-t.x, -t.y, -t.z);
	tinv.p = -t.p;
	transpose_and_scale_rotation(rot, &ret, rcps);
    ret.matrix[3] = ret.matrix[0] * tinv.x + ret.matrix[1] * tinv.y \
        + ret.matrix[2] * tinv.z;
    ret.matrix[7] = ret.matrix[4] * tinv.x + ret.matrix[5] * tinv.y \
        + ret.matrix[6] * tinv.z;
    ret.matrix[11] = ret.matrix[8] * tinv.x + ret.matrix[9] * tinv.y \
        + ret.matrix[10] * tinv.z;
    return (ret);
}
