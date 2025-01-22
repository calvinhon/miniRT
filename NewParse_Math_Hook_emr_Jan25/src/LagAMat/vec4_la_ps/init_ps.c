/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:13:08 by nth          #+#    #+#             */
/*   Updated: 2024/11/02 07:14:22 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

t_vec4s vec4s_re(float x, float y, float z, float w)
{
    t_vec4s v;
    v.a[0] = x;
    v.a[1] = y;
    v.a[2] = z;
    v.a[3] = w;
    return v;
}

void vec4s_ini(t_vec4s *v, float x, float y, float z, float w)
{
    v->a[0] = x;
    v->a[1] = y;
    v->a[2] = z;
    v->a[3] = w;
}

t_vec4s vec4sp_re(float x, float y, float z)
{
    return vec4s_re(x, y, z, 1.0f);
}

void vec4sp_ini(t_vec4s *p, float x, float y, float z)
{
    vec4s_ini(p, x, y, z, 1.0f);
}

t_vec4s vec4sv_re(float x, float y, float z)
{
    return vec4s_re(x, y, z, 0.0f);
}

void vec4sv_ini(t_vec4s *v, float x, float y, float z)
{
    vec4s_ini(v, x, y, z, 0.0f);
}
