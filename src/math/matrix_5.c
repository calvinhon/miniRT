/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:00:03 by chon              #+#    #+#             */
/*   Updated: 2025/01/16 16:09:54 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_math.h"

t_mat4d identity_mat(void)
{
	t_mat4d m;
	int i;
	int row;
	int col;

	i = -1;
	while (++i < 16)
	{
		row = i / 4;
		col = i % 4;
		if (row == col)
			m.matrix[i] = 1;
		else
			m.matrix[i] = 0;
	}
	return (m);
}

t_mat4d translation_mat(float x, float y, float z)
{
	t_mat4d m;

	m = identity_mat();
	m.matrix[3] = x;
	m.matrix[7] = y;
	m.matrix[11] = z;
	return (m);
}

t_mat4d scaling_mat(float x, float y, float z)
{
	t_mat4d m;

	m = identity_mat();
	m.matrix[0] = x;
	m.matrix[5] = y;
	m.matrix[10] = z;
	return (m);
}
