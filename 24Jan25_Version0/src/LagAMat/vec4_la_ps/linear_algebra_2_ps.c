/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_algebra_2_ps.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 03:28:04 by nth          #+#    #+#             */
/*   Updated: 2024/11/02 07:15:24 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

void	cross_vec4s(t_vec4s *out, const t_vec4s in1,
						const t_vec4s in2)
{
	*out = cross_vec4s_re(in1, in2);
}

t_vec4s	cross_vec4s_re(const t_vec4s in1,
						const t_vec4s in2)
{
	 t_vec4s result;

    result.a[0] = in1.a[1] * in2.a[2] - in1.a[2] * in2.a[1];
    result.a[1] = in1.a[2] * in2.a[0] - in1.a[0] * in2.a[2];
    result.a[2] = in1.a[0] * in2.a[1] - in1.a[1] * in2.a[0];
    result.a[3] = 0.0f; 
    return (result);
}
