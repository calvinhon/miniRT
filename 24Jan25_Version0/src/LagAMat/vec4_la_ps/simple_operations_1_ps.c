/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_operations_1_ps.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:57:10 by nth          #+#    #+#             */
/*   Updated: 2024/11/18 10:46:05 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

void	add_vec4s(t_vec4s *out, const t_vec4s *in1,
						const t_vec4s *in2)
{
    out->a[0] = in1->a[0] + in2->a[0];
    out->a[1] = in1->a[1] + in2->a[1];
    out->a[2] = in1->a[2] + in2->a[2];
    out->a[3] = in1->a[3] + in2->a[3];
}

t_vec4s	add_vec4s_re(const t_vec4s in1, const t_vec4s in2)
{
	t_vec4s result;

    result.a[0] = in1.a[0] + in2.a[0];
    result.a[1] = in1.a[1] + in2.a[1];
    result.a[2] = in1.a[2] + in2.a[2];
    result.a[3] = in1.a[3] + in2.a[3];
	
    return result;
}

void	sub_vec4s(t_vec4s *out, const t_vec4s *in1,
						const t_vec4s *in2)
{
    out->a[0] = in1->a[0] - in2->a[0];
    out->a[1] = in1->a[1] - in2->a[1];
    out->a[2] = in1->a[2] - in2->a[2];
    out->a[3] = in1->a[3] - in2->a[3];
}

t_vec4s	sub_vec4s_re(const t_vec4s in1, const t_vec4s in2)
{
    t_vec4s result;

    result.a[0] = in1.a[0] - in2.a[0];
    result.a[1] = in1.a[1] - in2.a[1];
    result.a[2] = in1.a[2] - in2.a[2];
    result.a[3] = in1.a[3] - in2.a[3];

    return result;
}
