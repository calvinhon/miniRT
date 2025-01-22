/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_algebra_1_ps.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:27:03 by nth          #+#    #+#             */
/*   Updated: 2024/11/18 10:22:16 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

void	dot_vec4s(float *out, const t_vec4s *in1, const t_vec4s *in2)
{
	*out = dot_vec4s_re(in1, in2);
}

float	dot_vec4s_re(const t_vec4s *v1,
							const t_vec4s *v2)
{
 return (v1->a[0] * v2->a[0] + v1->a[1] * v2->a[1] + \
  v1->a[2] * v2->a[2] + v1->a[3] * v2->a[3]);
}

void	magnitude_vec4s(float *out, const t_vec4s in)
{
	*out = magnitude_vec4s_re(in);
}

float	magnitude_vec4s_re(const t_vec4s in)
{
    return sqrtf(in.a[0] * in.a[0] +
                 in.a[1] * in.a[1] +
                 in.a[2] * in.a[2] +
                 in.a[3] * in.a[3]);
}
