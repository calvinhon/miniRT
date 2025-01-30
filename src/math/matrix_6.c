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

t_mat4d rotate_mat_x(float rad)
{
	t_mat4d m;

	m = identity_mat();
	m.matrix[5] = cos(rad);
	m.matrix[6] = -sin(rad);
	m.matrix[9] = sin(rad);
	m.matrix[10] = cos(rad);
	return (m);
}

t_mat4d rotate_mat_y(float rad)
{
	t_mat4d m;

	m = identity_mat();
	m.matrix[0] = cos(rad);
	m.matrix[2] = sin(rad);
	m.matrix[8] = -sin(rad);
	m.matrix[10] = cos(rad);
	return (m);
}

t_mat4d rotate_mat_z(float rad)
{
	t_mat4d m;

	m = identity_mat();
	m.matrix[0] = cos(rad);
	m.matrix[1] = -sin(rad);
	m.matrix[4] = sin(rad);
	m.matrix[5] = cos(rad);
	return (m);
}

t_mat4d shear_mat(t_shear s)
{
	t_mat4d m;

	m = identity_mat();
	m.matrix[1] = s.x_y;
	m.matrix[2] = s.x_z;
	m.matrix[4] = s.y_x;
	m.matrix[6] = s.y_z;
	m.matrix[8] = s.z_x;
	m.matrix[9] = s.z_y;
	return (m);
}
