/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_h.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:44:06 by chon              #+#    #+#             */
/*   Updated: 2024/12/19 00:26:08 by nthoach          ###   ########.fr       */
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
	printf("BONUS = %d", BONUS);
	//
	if (minirt) //test
		free(minirt); //test
	return (OK);
}
