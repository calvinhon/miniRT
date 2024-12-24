/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3parse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:52:37 by marvin            #+#    #+#             */
/*   Updated: 2024/12/19 01:10:59 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/minirt.h"

void	errors(int err_code, t_minirt *minirt)
{
	if (minirt)
		free_minirt(minirt);
	ft_putstr_fd(MS_ER[err_code], 2);
	exit(err_code);
}

void	check_filename(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 3)
		errors(ER_FILE, NULL);
	else if (!ft_strnstr(file + (len - 3), ".rt", len))
		errors(ER_FILE, NULL);
}


//minirt->n_threads = 4;
//minirt->threads = (t_threads *)malloc(sizeof(t_threads)*minirt->n_threads);
//minirt->graphic.mlx = mlx_init();
//minirt->graphic.win = mlx_new_window(minirt->graphic.mlx, WINDOW_W, WINDOW_L, "miniRT");
//minirt->graphic.img = mlx_new_image(minirt->graphic.mlx, WINDOW_W, WINDOW_L);
//minirt->graphic.addr = mlx_get_data_addr(minirt->graphic.img, &minirt->graphic.bpp, &minirt->graphic.l_len, &minirt->graphic.end);
//minirt->scene.light = (t_light *)malloc(minirt->scene.l * sizeof(t_light));
//minirt->scene.objs = (t_object *)malloc(minirt->scene.n_objs * sizeof(t_object));
//minirt->scene.objs[idx].data = malloc(sizeof(t_sphere));

t_minirt	*new_minirt(void)
{
	t_minirt	*minirt;

	minirt = ft_calloc(1, sizeof(t_minirt));
	if (!minirt)
		errors(ER_MALLOC, NULL);
	return (minirt);
}

void	allocate_light_obj(t_minirt *minirt)
{
	minirt->scene.light = (t_light *)malloc(minirt->scene.l * sizeof(t_light));
	if (!minirt->scene.light)
		errors(ER_MALLOC, minirt);
	minirt->scene.objs = (t_object *)malloc(minirt->scene.n_objs * sizeof(t_object));
	if (!minirt->scene.objs)
		errors(ER_MALLOC, minirt);
}

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
	allocate_light_obj(minirt);
	parse_data(minirt, data);
	free(data);
}
