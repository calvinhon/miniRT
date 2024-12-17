/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:52:37 by marvin            #+#    #+#             */
/*   Updated: 2024/12/11 16:52:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	parse(t_minirt *minirt, char *file)
{
	char	*data;
	size_t	total_size;

	total_size = 0;
	data = NULL;
	data = file_data(minirt, &total_size, file);
	if (!data || total_size == 0)
	{
		free(data);
		errors(ER_EMPTY_MAP, minirt);
	}
	// test 1
	ft_printf("total size = %d \n", total_size); //
	ft_printf("data = %s\n", data);
	ft_printf("objs = %d\n", minirt->scene.n_objs);
	ft_printf("ambient = %d\n", minirt->scene.a);
	ft_printf("camera = %d\n", minirt->scene.c);
	ft_printf("light = %d\n", minirt->scene.l);
	ft_printf("plane = %d\n", minirt->scene.pl);	
	ft_printf("sphere = %d\n", minirt->scene.sp);
	ft_printf("cylinder = %d\n", minirt->scene.cy);	
	ft_printf("cubic = %d\n", minirt->scene.cu);	
	ft_printf("cone = %d\n", minirt->scene.co);		
	//
	//allocate_light_obj(minirt);
	// parse_data(minirt, data);
	free(data);
}
