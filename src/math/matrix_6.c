/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:01:32 by chon              #+#    #+#             */
/*   Updated: 2025/01/22 11:01:32 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_math.h"

t_mat4d	rotate_mat_x(float rad)
{
	t_mat4d	m;

	m.matrix[0] = 1.0f;
	m.matrix[1] = 0.0f;
	m.matrix[2] = 0.0f;
	m.matrix[3] = 0.0f;
	m.matrix[4] = 0.0f;
	m.matrix[5] = cosf(rad);
	m.matrix[6] = -sinf(rad);
	m.matrix[7] = 0.0f;
	m.matrix[8] = 0.0f;
	m.matrix[9] = sinf(rad);
	m.matrix[10] = cosf(rad);
	m.matrix[11] = 0.0f;
	m.matrix[12] = 0.0f;
	m.matrix[13] = 0.0f;
	m.matrix[14] = 0.0f;
	m.matrix[15] = 1.0f;
	return (m);
}

t_mat4d	rotate_mat_y(float rad)
{
	t_mat4d	m;

	m.matrix[0] = cosf(rad);
	m.matrix[1] = 0.0f;
	m.matrix[2] = sinf(rad);
	m.matrix[3] = 0.0f;
	m.matrix[4] = 0.0f;
	m.matrix[5] = 1.0f;
	m.matrix[6] = 0.0f;
	m.matrix[7] = 0.0f;
	m.matrix[8] = -sinf(rad);
	m.matrix[9] = 0.0f;
	m.matrix[10] = cosf(rad);
	m.matrix[11] = 0.0f;
	m.matrix[12] = 0.0f;
	m.matrix[13] = 0.0f;
	m.matrix[14] = 0.0f;
	m.matrix[15] = 1.0f;
	return (m);
}

t_mat4d	rotate_mat_z(float rad)
{
	t_mat4d	m;

	m.matrix[0] = cosf(rad);
	m.matrix[1] = -sinf(rad);
	m.matrix[2] = 0.0f;
	m.matrix[3] = 0.0f;
	m.matrix[4] = sinf(rad);
	m.matrix[5] = cosf(rad);
	m.matrix[6] = 0.0f;
	m.matrix[7] = 0.0f;
	m.matrix[8] = 0.0f;
	m.matrix[9] = 0.0f;
	m.matrix[10] = 1.0f;
	m.matrix[11] = 0.0f;
	m.matrix[12] = 0.0f;
	m.matrix[13] = 0.0f;
	m.matrix[14] = 0.0f;
	m.matrix[15] = 1.0f;
	return (m);
}

t_mat4d	shear_mat(t_shear s)
{
	t_mat4d	m;

	m.matrix[0] = 1.0f;
	m.matrix[1] = s.x_y;
	m.matrix[2] = s.x_z;
	m.matrix[3] = 0.0f;
	m.matrix[4] = s.y_x;
	m.matrix[5] = 1.0f;
	m.matrix[6] = s.y_z;
	m.matrix[7] = 0.0f;
	m.matrix[8] = s.z_x;
	m.matrix[9] = s.z_y;
	m.matrix[10] = 1.0f;
	m.matrix[11] = 0.0f;
	m.matrix[12] = 0.0f;
	m.matrix[13] = 0.0f;
	m.matrix[14] = 0.0f;
	m.matrix[15] = 1.0f;
	return (m);
}

//t_mat4d	rotate_mat_x(float rad)
//{
//	t_mat4d	m;

//	m = identity_mat();
//	m.matrix[5] = cosf(rad);
//	m.matrix[6] = -sinf(rad);
//	m.matrix[9] = sinf(rad);
//	m.matrix[10] = cosf(rad);
//	return (m);
//}

//t_mat4d	rotate_mat_y(float rad)
//{
//	t_mat4d	m;

//	m = identity_mat();
//	m.matrix[0] = cosf(rad);
//	m.matrix[2] = sinf(rad);
//	m.matrix[8] = -sinf(rad);
//	m.matrix[10] = cosf(rad);
//	return (m);
//}

//t_mat4d	rotate_mat_z(float rad)
//{
//	t_mat4d	m;

//	m = identity_mat();
//	m.matrix[0] = cosf(rad);
//	m.matrix[1] = -sinf(rad);
//	m.matrix[4] = sinf(rad);
//	m.matrix[5] = cosf(rad);
//	return (m);
//}

//t_mat4d	shear_mat(t_shear s)
//{
//	t_mat4d	m;

//	m = identity_mat();
//	m.matrix[1] = s.x_y;
//	m.matrix[2] = s.x_z;
//	m.matrix[4] = s.y_x;
//	m.matrix[6] = s.y_z;
//	m.matrix[8] = s.z_x;
//	m.matrix[9] = s.z_y;
//	return (m);
//}
