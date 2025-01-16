/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4s_cross.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:44:27 by nth          #+#    #+#             */
/*   Updated: 2024/11/18 10:12:59 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

void	cross_mat4s_vec4s(const t_mat4s *m,
							const t_vec4s *v, t_vec4s *out)
{
    out->x = dot_vec4s_re(&m->r1, v);
    out->y = dot_vec4s_re(&m->r2, v);
    out->z = dot_vec4s_re(&m->r3, v);
    out->w = dot_vec4s_re(&m->r4, v);
}


void	cross_mat4s_mat4s(const t_mat4s in1,
						const t_mat4s in2, t_mat4s *out)
{
    int i;
	int j;

	i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            out->a[i][j] = in1.a[i][0] * in2.a[0][j] +
                           in1.a[i][1] * in2.a[1][j] +
                           in1.a[i][2] * in2.a[2][j] +
                           in1.a[i][3] * in2.a[3][j];
            j++;
        }
        i++;
    }
}
