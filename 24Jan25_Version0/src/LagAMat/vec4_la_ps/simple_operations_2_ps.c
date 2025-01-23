/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_operations_2_ps.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:24:33 by nth          #+#    #+#             */
/*   Updated: 2024/11/02 07:16:36 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

void	scale_vec4s(t_vec4s *out, const t_vec4s in,
						float scalar)
{
    out->a[0] = in.a[0] * scalar;
    out->a[1] = in.a[1] * scalar;
    out->a[2] = in.a[2] * scalar;
    out->a[3] = in.a[3] * scalar;
}

t_vec4s	scale_vec4s_re(const t_vec4s in, float scalar)
{
	t_vec4s result;

    result.a[0] = in.a[0] * scalar;
    result.a[1] = in.a[1] * scalar;
    result.a[2] = in.a[2] * scalar;
    result.a[3] = in.a[3] * scalar;

    return result;
}

void	negate_vec4s_new(t_vec4s *out, const t_vec4s in)
{
    out->a[0] = -in.a[0];
    out->a[1] = -in.a[1];
    out->a[2] = -in.a[2];
    out->a[3] = -in.a[3];
}

void	negate_vec4s(t_vec4s *target)
{
    target->a[0] = -target->a[0];
    target->a[1] = -target->a[1];
    target->a[2] = -target->a[2];
    target->a[3] = -target->a[3];
}

t_vec4s	negate_vec4s_re(const t_vec4s in)
{
	t_vec4s result;

    result.a[0] = -in.a[0];
    result.a[1] = -in.a[1];
    result.a[2] = -in.a[2];
    result.a[3] = -in.a[3];

    return result;
}
