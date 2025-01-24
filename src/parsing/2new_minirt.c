/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2new_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:00:25 by marvin            #+#    #+#             */
/*   Updated: 2024/12/18 23:50:39 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/minirt.h"

t_minirt	*new_minirt(void)
{
	t_minirt	*minirt;

	minirt = ft_calloc(1, sizeof(t_minirt));
	if (!minirt)
		errors(ER_MALLOC, NULL);
	*minirt = (t_minirt){0};
	return (minirt);
}
