/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 06:06:16 by nth          #+#    #+#             */
/*   Updated: 2024/10/07 09:26:22 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "macros.h"

void	errors(int err_code, char *err_ms, void *ptr)
{
	t_minirt	*minirt;

	minirt = (t_minirt *)ptr;
	if (minirt)
		free_minirt(minirt);
	ft_putstr_fd(err_ms, 2);
	exit(err_code);
}

int	destroy_minirt(t_minirt *minirt)
{
	free_minirt(minirt);
	exit(0);
	return (0);
}
