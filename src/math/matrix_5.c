/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:00:03 by chon              #+#    #+#             */
/*   Updated: 2024/12/16 15:17:02 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_math.h"

t_mat4d	identity_mat(void)
{
	t_mat4d	m;
	int		i;
	int		row;
	int		col;

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

t_mat4d	translation_mat(double x, double y, double z)
{
	t_mat4d	m;

	m = identity_mat();
	m.matrix[3] = x;
	m.matrix[7] = y;
	m.matrix[11] = z;
	return (m);
}

t_mat4d	scaling_mat(double x, double y, double z)
{
	t_mat4d	m;
	int		i;
	int		row;
	int		col;

	i = -1;
	while (++i < 16)
	{
		row = i / 4;
		col = i % 4;
		if (row == col && !row)
			m.matrix[i] = x;
		else if (row == col && row == 1)
			m.matrix[i] = y;
		else if (row == col && row == 2)
			m.matrix[i] = z;
		else if (row == col)
			m.matrix[i] = 1;
		else
			m.matrix[i] = 0;
	}
	return (m);
}
