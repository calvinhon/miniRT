/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 06:45:19 by nth          #+#    #+#             */
/*   Updated: 2024/11/18 10:24:52 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

t_vec4s	normalize_vec4s_medp(const t_vec4s in)
{
    float msqr;
    t_vec4s result;
    float sqrt_msqr;

    msqr = in.a[0] * in.a[0] + in.a[1] * in.a[1] + in.a[2] * in.a[2] + in.a[3] * in.a[3];
    if (msqr == 0.0f)
        return (t_vec4s){.a = {0.f, 0.f, 0.f, 0.f}};
    sqrt_msqr = sqrtf(msqr);
    result.a[0] = in.a[0] / sqrt_msqr;
    result.a[1] = in.a[1] / sqrt_msqr;
    result.a[2] = in.a[2] / sqrt_msqr;
    result.a[3] = in.a[3] / sqrt_msqr;
    return result;
}

t_vec4s	normalize_vec4s_highp(const t_vec4s in)
{
    float msqr;
    float sqrt_msqr;
    t_vec4s result;

    msqr = in.a[0] * in.a[0] + in.a[1] * in.a[1] + in.a[2] * in.a[2] + in.a[3] * in.a[3];

    if (msqr == 0.0f)
        return (vec4s_re(0.f, 0.f, 0.f, 0.f));

    sqrt_msqr = sqrtf(msqr);

    result.a[0] = in.a[0] / sqrt_msqr;
    result.a[1] = in.a[1] / sqrt_msqr;
    result.a[2] = in.a[2] / sqrt_msqr;
    result.a[3] = in.a[3] / sqrt_msqr;

    return result;
}
