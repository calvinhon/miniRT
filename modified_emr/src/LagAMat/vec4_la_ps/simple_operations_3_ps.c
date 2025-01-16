/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_operations_3_ps.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:47:28 by nth          #+#    #+#             */
/*   Updated: 2024/11/18 10:49:13 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

bool	equal_vec4s(const t_vec4s v1, const t_vec4s v2,
						float tolerance)
{
    return (fabsf(v1.a[0] - v2.a[0]) < tolerance &&
            fabsf(v1.a[1] - v2.a[1]) < tolerance &&
            fabsf(v1.a[2] - v2.a[2]) < tolerance &&
            fabsf(v1.a[3] - v2.a[3]) < tolerance);
}

void	normalize_vec4s(t_vec4s *target)
{
    float msqr;
 
    msqr = target->a[0] * target->a[0] + target->a[1] * target->a[1] \
        + target->a[2] * target->a[2] + target->a[3] * target->a[3];
    if (msqr == 0.0f)
    {
        *target = vec4sv_re(0.f, 0.f, 0.f);
        return ;
    }
    *target = scale_vec4s_re(*target, 1.f /sqrtf(msqr));
}

t_vec4s	normalize_vec4s_re(const t_vec4s in)
{
	float msqr; 
	
    msqr = in.a[0] * in.a[0] + in.a[1] * in.a[1] + in.a[2] * in.a[2] + \
     in.a[3] * in.a[3];

    if (msqr == 0.0f)
        return (vec4sv_re(0.f, 0.f, 0.f));
    return (scale_vec4s_re(in, 1.f / sqrtf(msqr)));
}

void	normalize_vec4s_new(t_vec4s *out, const t_vec4s in)
{
	float msqr; 

    msqr = in.a[0] * in.a[0] + in.a[1] * in.a[1] + in.a[2] * in.a[2] + \
     in.a[3] * in.a[3];

    if (msqr == 0.0f)
    {
        *out = vec4sv_re(0.f, 0.f, 0.f);
        return;
    }
    *out = scale_vec4s_re(in, 1.f /sqrtf(msqr));
}
