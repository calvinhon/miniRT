/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31read_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:22:13 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/19 01:03:27 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/minirt.h"

void	count_elements(t_minirt *minirt, char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (ft_strnstr(line, "A ", len))
		minirt->scene.a++;
	if (ft_strnstr(line, "C ", len))
		minirt->scene.c++;
	if ((ft_strnstr(line, "l ", len) || \
		ft_strnstr(line, "L", len)) && !ft_strnstr(line, "pl ", len))
		minirt->scene.l++;
	if (ft_strnstr(line, "pl ", len))
		minirt->scene.pl++;
	if (ft_strnstr(line, "sp ", len))
		minirt->scene.sp++;
	if (ft_strnstr(line, "cy ", len))
		minirt->scene.cy++;
	if (ft_strnstr(line, "cu ", len))
		minirt->scene.cu++;
	if (ft_strnstr(line, "co ", len))
		minirt->scene.co++;
}

void	check_elements(t_minirt *minirt)
{
	if (minirt->scene.c != 1)
		errors(ER_ONE_CAMERA, minirt);
	if (minirt->scene.a != 1)
		errors(ER_ONE_AMBIENT, minirt);
	if (minirt->scene.l == 0)
		errors(ER_NO_LIGHT, minirt);
	if (minirt->scene.l > MAX_LIGHT)
		errors(ER_MAX_LIGHT, minirt);
	minirt->scene.n_objs = minirt->scene.pl + minirt->scene.sp + \
		minirt->scene.cy + minirt->scene.cu + minirt->scene.co;
	if (minirt->scene.n_objs == 0)
		errors(ER_NO_OBJ, minirt);
}

size_t	calculate_required_size(char *file, t_minirt *minirt)
{
	char	*line;
	int		fd;
	size_t	total_size;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		errors(ER_OPEN_FILE, minirt);
	total_size = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strchr("\n#", line[0]))
		{
			total_size += ft_strlen(line);
			count_elements(minirt, line);
		}
		free(line);
	}
	close(fd);
	check_elements(minirt);
	return (total_size);
}

char	*file_data(t_minirt *minirt, size_t *total_size, char *file)
{
	int		fd;
	char	*line;
	char	*data;
	size_t	line_len;

	data = ft_calloc(calculate_required_size(file, minirt) + 1, sizeof(char));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		errors(ER_OPEN_FILE, minirt);
	while (1)
	{
		line = get_next_line(fd);
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
	data[*(total_size)] = '\0';
	close(fd);
	return (data);
}
