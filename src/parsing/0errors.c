/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0errors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:39:11 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/17 11:53:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	errors(int err_code, t_minirt *minirt)
{
	//close_minirt(minirt);
	if (minirt)
		free(minirt); //
	if (err_code == ER_AGC)
		ft_putstr_fd(MS_USAGE, 2);
	else if (err_code == ER_FILE)
		ft_putstr_fd(MS_NOT_RT, 2);
	else if (err_code == ER_NOT_RT)
		ft_putstr_fd(MS_NOT_RT, 2);
	else
		ft_putstr_fd(MS_OTHERS, 2);
	exit(err_code);
}