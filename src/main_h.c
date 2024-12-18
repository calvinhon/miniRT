/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_h.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:44:06 by chon              #+#    #+#             */
/*   Updated: 2024/12/19 01:21:02 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minirt.h"
#include "../include/parsing.h"

int	main(int ac, char **av)
{
	t_minirt	*minirt;

	if (ac != 2)
		errors(ER_AGC, NULL);
	check_filename(av[1]);
	minirt = new_minirt();
	parse(minirt, av[1]);
	// ini_all(minirt);
	// ray_trace(minirt);
	// free_minirt(minirt);

	// test
		// test 1
	ft_printf("objs = %d\n", minirt->scene.n_objs);
	ft_printf("ambient = %d\n", minirt->scene.a);
	ft_printf("camera = %d\n", minirt->scene.c);
	ft_printf("light = %d\n", minirt->scene.l);
	ft_printf("n_objs = %d\n", minirt->scene.n_objs);	
	
		// test 2
	printf("BONUS = %d\n", BONUS);
		//test
	printf("A.intensity = %f\n", minirt->scene.ambient.intensity);
	printf("A.color = %d, %d, %d\n", minirt->scene.ambient.color.r, \
		minirt->scene.ambient.color.g, minirt->scene.ambient.color.b);
	printf("C.position = %f, %f, %f\n", minirt->scene.camera.origin.x, \
		minirt->scene.camera.origin.y, minirt->scene.camera.origin.z);
	printf("C.fov = %f\n", minirt->scene.camera.fov);// test
	
	size_t idx = -1;
	while ( ++idx < minirt->scene.l)
	{
		printf("light[%ld]. = %f\n", idx, minirt->scene.light[idx].brightness);// test
	}
	
	idx = -1;
	while ( ++idx < minirt->scene.n_objs)
	{
		printf("objects[%ld].type = %i\n", idx, minirt->scene.objs[idx].type);// test
		printf("objects[%ld].brightness = %f\n", idx, minirt->scene.objs[idx].reflection);// test
	}

	if (minirt) //test
		free(minirt); //test
	return (OK);
}
