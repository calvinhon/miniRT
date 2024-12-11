/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:15:15 by marvin            #+#    #+#             */
/*   Updated: 2024/12/11 18:15:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

char *read_file(t_minirt *minirt, char *file)
{
    int		fd;
	int		i;
	char	*line;
	char	*data;

	i = 0;
	data = ft_calloc(1, get_size(file) * sizeof(char));
	if (!data)
		errors(ER_MALLOC(": data malloc"), minirt);
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
            data = line;
            data += ft_strlen(line);
        }		
		else
			free(line);
	}
	close(fd);
	return (data);
}