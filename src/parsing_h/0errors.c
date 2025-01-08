/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0errors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:39:11 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/25 15:24:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	errors(int err_code, t_minirt *minirt)
{
	//close_minirt(minirt);
	if (minirt)
		free(minirt); //
	ft_putstr_fd(MS_ER[err_code], 2);
	exit(err_code);
}