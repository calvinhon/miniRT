/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 03:10:59 by nth          #+#    #+#             */
/*   Updated: 2024/10/16 13:29:29 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"

char	*file_data(t_minirt *minirt, size_t *total_size, char *file)
{
	int		fd;
	char	*line;
	char	*data;
	size_t	line_len;

	data = ft_calloc(calculate_required_size(file, minirt) + 1, sizeof(char));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (errors(CER_OPEN_FILE, ER_OPEN_FILE, minirt), NULL);
	while (1)
	{
		line = get_next_line_err(fd, 0);
		if (!line)
			break ;
		if (!ft_strchr("\n#", line[0]))
		{
			line_len = ft_strlen(line);
			ft_memcpy(data + *total_size, line, line_len);
			*total_size += line_len;
		}
		free(line);
	}
	data[*total_size] = '\0';
	get_next_line_err(fd, 1);
	return (close(fd), data);
}

void	allocate_light_shape(t_minirt *minirt)
{
	minirt->scene.lights = (t_light *)malloc(minirt->scene.num_lights \
		* sizeof(t_light));
	if (!minirt->scene.lights)
		errors(CER_MALLOC, ER_MALLOC, minirt);
	minirt->scene.shapes = (t_object *)malloc(minirt->scene.num_shapes \
		* sizeof(t_object));
	if (!minirt->scene.shapes)
		errors(CER_MALLOC, ER_MALLOC, minirt);
}

void	parse(char *file, t_minirt *minirt)
{
	size_t	total_size;

	total_size = 0;
	minirt->data = file_data(minirt, &total_size, file);
	if (total_size == 0)
		return (free(minirt->data), errors(CER_EMPTY_MAP, \
			ER_EMPTY_MAP, minirt));
	allocate_light_shape(minirt);
	parse_data(minirt, minirt->data, total_size);
	if (minirt->data)
		free(minirt->data);
	minirt->data = NULL;
}
