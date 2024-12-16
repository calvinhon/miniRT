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

#include "../../include/minirt.h"

t_minirt	*new_minirt(void)
{
	t_minirt	*minirt;

	minirt = ft_calloc(1, sizeof(t_minirt));
	if (!minirt)
		errors(ER_MALLOC, NULL);
	minirt->graphic.mlx = NULL;
	minirt->graphic.win = NULL;
	minirt->graphic.img = NULL;
	minirt->graphic.addr = NULL;
	minirt->graphic.bpp = 0;
	minirt->graphic.l_len = 0;
	minirt->graphic.end = 0;

	minirt->scene.ambient.intensity = 0.0f;
	minirt->scene.ambient.color = (t_color){0, 0, 0, 0};

	minirt->scene.camera.origin = (t_point){0.0f, 0.0f, 0.0f, 1.0f};
	minirt->scene.camera.direction = (t_vector){0.0f, 0.0f, -1.0f, 0.0f};
	minirt->scene.camera.fov = 90.0f;

	minirt->scene.light = NULL;
	minirt->scene.objects = NULL;
	minirt->scene.a = 0;
	minirt->scene.c = 0;
	minirt->scene.l = 0;
	minirt->scene.pl = 0;
	minirt->scene.sp = 0;
	minirt->scene.cy = 0;
	minirt->scene.cu = 0;
	minirt->scene.co = 0;
	minirt->threads = NULL;
	return (minirt);
}
