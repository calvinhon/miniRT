/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3parse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:52:37 by marvin            #+#    #+#             */
/*   Updated: 2024/12/19 00:56:44 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/minirt.h"

void	allocate_light_obj(t_minirt *minirt)
{
	minirt->scene.light = (t_light *)malloc(minirt->scene.l * sizeof(t_light));
	if (!minirt->scene.light)
		errors(ER_MALLOC, minirt);
	minirt->scene.objs = (t_object *)malloc(minirt->scene.n_objs * sizeof(t_object));
	if (!minirt->scene.objs)
		errors(ER_MALLOC, minirt);
	ft_printf("allocate ok\n"); //test
}

void	parse(t_minirt *minirt, char *file)
{
	char	*data;
	size_t	total_size;

	total_size = 0;
	data = NULL;
	printf("ok-0\n");
	data = file_data(minirt, &total_size, file);
	printf("ok-1\n");
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
	allocate_light_obj(minirt);
	parse_data(minirt, data);
	//test
	// printf("A.intensity = %f\n", minirt->scene.ambient.intensity);
	// printf("A.color = %d, %d, %d\n", minirt->scene.ambient.color.r, \
	// 	minirt->scene.ambient.color.g, minirt->scene.ambient.color.b);
	// printf("C.position = %f, %f, %f\n", minirt->scene.camera.origin.x, \
	// 	minirt->scene.camera.origin.y, minirt->scene.camera.origin.z);
	// //
	free(data);
	
}
