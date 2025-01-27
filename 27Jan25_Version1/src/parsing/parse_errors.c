/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:38:59 by nth               #+#    #+#             */
/*   Updated: 2025/01/14 18:20:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"

bool	count_elements(t_minirt *minirt, char *line)
{
	while (*line == ' ')
		line++;
	if (*line == 'A' && *(line + 1) == ' ')
		minirt->scene.num_a++;
	else if (*line == 'C' && *(line + 1) == ' ')
		minirt->scene.num_c++;
	else if (((*line == 'L' || *line == 'l') && *(line + 1) == ' ') || \
		((*line == 'S' || *line == 's') && (*(line + 1) == 'L' \
			|| *line == 'l') && *(line + 2) == ' '))
		minirt->scene.num_lights++;
	else if ((*line == 's' && *(line + 1) == 'p' && *(line + 2) == ' ') || \
		(*line == 'p' && *(line + 1) == 'l' && *(line + 2) == ' ') || \
		(*line == 'c' && *(line + 1) == 'y' && *(line + 2) == ' ') || \
		(*line == 'c' && *(line + 1) == 'u' && *(line + 2) == ' ') || \
		(*line == 'c' && *(line + 1) == 'o' && *(line + 2) == ' '))
		minirt->scene.num_shapes++;
	else
		return (printf("Unknown element: %c%c\n", *line, \
			*(line + 1)), free(line), false);
	return (true);
}

void	check_elements(t_minirt *minirt)
{
	if (minirt->scene.num_c != 1)
	{
		ft_printf("Number of camera: %d\n", minirt->scene.num_c);
		errors(CER_ONE_CAMERA, ER_ONE_CAMERA, minirt);
	}
	if (minirt->scene.num_a != 1)
	{
		ft_printf("Number of ambient: %d\n", minirt->scene.num_a);
		errors(CER_ONE_AMBIENT, ER_ONE_AMBIENT, minirt);
	}
	if (minirt->scene.num_lights == 0)
	{
		ft_printf("There is no light\n");
		errors(CER_NO_LIGHT, ER_NO_LIGHT, minirt);
	}
	if (minirt->scene.num_lights > LIGHTS_MAX)
		errors(CER_MAX_LIGHT, ER_MAX_LIGHT, minirt);
	if (minirt->scene.num_shapes == 0)
	{
		ft_printf("There is no object\n");
		errors(CER_NO_OBJ, ER_NO_OBJ, minirt);
	}
	if (minirt->scene.num_shapes > SHAPES_MAX)
		errors(CER_MAX_SHAPES, ER_MAX_SHAPES, minirt);
}

static size_t	check_errors(int fd, size_t total_size, t_minirt *minirt)
{
	close(fd);
	if (total_size == 0)
		return (ft_printf("file empty.\n"),
			errors(CER_EMPTY_MAP, ER_EMPTY_MAP, minirt), 1);
	check_elements(minirt);
	return (total_size);
}

// Helper function: Calculate the memory required
size_t	calculate_required_size(char *file, t_minirt *minirt)
{
	char	*line;
	int		fd;
	size_t	total_size;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		errors(CER_OPEN_FILE, ER_OPEN_FILE, minirt);
	total_size = 0;
	while (1)
	{
		line = get_next_line_err(fd, 0);
		if (!line)
			break ;
		if (!ft_strchr("\n#", line[0]))
		{
			total_size += ft_strlen(line);
			if (!count_elements(minirt, line))
			{
				get_next_line_err(fd, 1);
				errors(CER_OBJ_TYPE, ER_OBJ_TYPE, minirt);
			}
		}
		free(line);
	}
	return (check_errors(fd, total_size, minirt));
}
