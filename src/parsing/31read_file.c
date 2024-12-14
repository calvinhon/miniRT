/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31read_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:22:13 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/14 17:22:13 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

// Helper function: Calculate the memory required
size_t	calculate_required_size(char *file, t_minirt *minirt)
{
	char	*line;
	int		fd;
	size_t	total_size;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		errors(ER_OPEN_FILE, minirt);
	total_size = 0;
	while ((line = get_next_line(fd)))
	{
		if (!ft_strchr("\n#", line[0]))
			total_size += ft_strlen(line);
		free(line);
	}
	close(fd);
	return (total_size);
}


char	*file_data(t_minirt *minirt, size_t *total_size, char *file)
{
	int		fd;
	char	*line;
	char	*data;
	size_t	size;
	size_t	line_len;

	size = calculate_required_size(file, minirt);
	data = ft_calloc(size, sizeof(char));
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
	close(fd);
	return (data);
}