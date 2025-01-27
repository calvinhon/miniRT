/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:39:29 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 17:34:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include "macros.h"

t_frame	*rt_xpm_file_to_canvas(char *filepath, void *mlx)
{
	t_frame	*retval;

	retval = malloc(sizeof(t_frame));
	if (!retval)
		return (NULL);
	retval->ptr = mlx_xpm_file_to_image(mlx, filepath,
			&retval->tex_width, &retval->tex_height);
	if (!retval->ptr)
	{
		free(retval);
		return (NULL);
	}
	retval->addr = mlx_get_data_addr(retval->ptr, &retval->bpp,
			&retval->line_length, &retval->endian);
	retval->bpp_8 = retval->bpp / 8;
	return (retval);
}
