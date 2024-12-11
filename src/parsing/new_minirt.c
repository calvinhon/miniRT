/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_minirt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:00:25 by marvin            #+#    #+#             */
/*   Updated: 2024/12/11 18:00:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_minirt	*new_minirt(void)
{
	t_minirt	*minirt;

	minirt = ft_calloc(1, sizeof(t_minirt));
	if (!minirt)
		return (NULL);
	minirt->objs = new_obj((void *)&copy_obj, NULL, &free, (void *)&write_obj);
	minirt->lights = new_light((void *)&copy_light, NULL, &free, (void *)&light_print);
	return (minirt);
}