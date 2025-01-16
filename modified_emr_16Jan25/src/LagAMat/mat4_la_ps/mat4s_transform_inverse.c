/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4s_transform_inverse.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:34:23 by nth          #+#    #+#             */
/*   Updated: 2024/11/18 10:19:38 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

/*Process documented in https://docs.google.com/document/d/1ok8dzMk7EZiZaVRB61zGDlxRSDoelX3z6ixaCRlg0yM/edit?usp=sharing*/

t_mat4s get_inv_tranform_mat4s(const t_mat4s rot, const t_vec4s s, const t_vec4s t)
{
    t_mat4s ret;
    t_vec4s rcps, tinv;

    // Check for zero components in the scaling vector
    //if (s.a[0] == 0.0f || s.a[1] == 0.0f || s.a[2] == 0.0f)
    //{
    //    fprintf(stderr, "Error: Zero component in scaling vector\n");
    //    exit(EXIT_FAILURE);
    //}

    // Calculate reciprocal of scaling factors
    rcps.a[0] = 1.f / s.a[0];
    rcps.a[1] = 1.f / s.a[1];
    rcps.a[2] = 1.f / s.a[2];
    rcps.a[3] = 1.f; // No scaling for the w component

    // Negate the translation vector
    tinv.a[0] = -t.a[0];
    tinv.a[1] = -t.a[1];
    tinv.a[2] = -t.a[2];
    tinv.a[3] = -t.a[3];

    // Transpose the rotation matrix
    ret.a[0][0] = rot.a[0][0];
    ret.a[0][1] = rot.a[1][0];
    ret.a[0][2] = rot.a[2][0];
    ret.a[0][3] = 0.f;

    ret.a[1][0] = rot.a[0][1];
    ret.a[1][1] = rot.a[1][1];
    ret.a[1][2] = rot.a[2][1];
    ret.a[1][3] = 0.f;

    ret.a[2][0] = rot.a[0][2];
    ret.a[2][1] = rot.a[1][2];
    ret.a[2][2] = rot.a[2][2];
    ret.a[2][3] = 0.f;

    ret.a[3][0] = 0.f;
    ret.a[3][1] = 0.f;
    ret.a[3][2] = 0.f;
    ret.a[3][3] = 1.f;

    // Scale the transposed rotation matrix by the reciprocal scaling factors
    for (int i = 0; i < 3; ++i)
    {
        ret.a[i][0] *= rcps.a[0];
        ret.a[i][1] *= rcps.a[1];
        ret.a[i][2] *= rcps.a[2];
    }

    // Calculate the translation part
    ret.a[0][3] = ret.a[0][0] * tinv.a[0] + ret.a[0][1] * tinv.a[1] + ret.a[0][2] * tinv.a[2];
    ret.a[1][3] = ret.a[1][0] * tinv.a[0] + ret.a[1][1] * tinv.a[1] + ret.a[1][2] * tinv.a[2];
    ret.a[2][3] = ret.a[2][0] * tinv.a[0] + ret.a[2][1] * tinv.a[1] + ret.a[2][2] * tinv.a[2];

    return ret;
}