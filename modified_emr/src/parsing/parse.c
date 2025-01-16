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

bool	parse_uppercase_object(t_minirt *minirt, const char *info,
			int curr_line)
{
	t_split	split;

	split = ft_split(info, " ");
	if (!split.array)
		errors(CER_MALLOC, ER_MALLOC, minirt);
	if (*info == 'A')
		return (parse_ambient(minirt, &split, curr_line));
	if (*info == 'C')
		return (parse_camera(minirt, &split, curr_line));
	if (*info == 'L')
		return (parse_light(minirt, &split, curr_line));
	destroy_2d_arr(split.array);
	return (true);
}
bool	check_object_validity_and_add(t_minirt *minirt, const char *info,
			int curr_line, size_t line_len)
{
	const t_split	fields = ft_split(info, " ");

	if (!ft_isalpha(*info))
		return (destroy_2d_arr(fields.array),
			parse_syn_err_msg((char *)info, curr_line), false);
	if (*info == 'A' || *info == 'C' || *info == 'L')
	{
		if (line_len > 1 && *(info + 1) != ' ')
			return (destroy_2d_arr(fields.array),
				parse_syn_err_msg((char *)info, curr_line), false);
		return (destroy_2d_arr(fields.array),
			parse_uppercase_object(minirt, info, curr_line));
	}
	return (check_object_validity_init(minirt, info, curr_line, fields));
}

bool	read_file_ext(t_gnl *line, t_minirt *minirt, int curr_line,
		const char *filename)
{
	if (line->error)
		return (parse_fatal_msg("Allocation failure", curr_line), false);
	if ((line->eof && curr_line == 1)
		|| (minirt->scene.num_lights == 0 || minirt->scene.num_shapes == 0)
		|| (!minirt->ambiance.is_set || !minirt->cam.is_set))
	{
		if (line->line)
			free(line->line);
		ft_putstr_fd("Error: file `", STDERR_FILENO);
		ft_putstr_fd((char *)filename, STDERR_FILENO);
		ft_putendl_fd("` appears to be incomplete. Need:", STDERR_FILENO);
		if (!minirt->scene.num_lights)
			ft_putendl_fd("\tAt least one light.", 2);
		if (!minirt->scene.num_shapes)
			ft_putendl_fd("\tAt least one shape.", 2);
		if (!minirt->ambiance.is_set)
			ft_putendl_fd("\tExactly one value for global Ambiance lighting.",
				2);
		if (!minirt->cam.is_set)
			ft_putendl_fd("\tExactly one camera.", 2);
		return (false);
	}
	return (true);
}

bool	read_file(int fd, t_minirt *minirt, const char *filename)
{
	t_gnl		line;
	uint32_t	curr_line;

	line = get_next_line(fd);
	curr_line = 1;
	while (!line.error && !line.eof)
	{
		if (*line.line == '\n' || *line.line == '#')
		{
			(free(line.line), curr_line++);
			line = get_next_line(fd);
			continue ;
		}
		if (!check_object_validity_and_add(minirt, line.line, curr_line++,
				line.len))
		{
			ft_putstr_fd((char *)filename, 2);
			ft_putstr_fd(":\n\t", 2);
			ft_putendl_fd(line.line, 2);
			return ((void)close(fd), free(line.line), \
			 errors(CER_SYNTAX, ER_SYNTAX, minirt), false);
		}
		free(line.line);
		line = get_next_line(fd);
	}
	return (close(fd), read_file_ext(&line, minirt, curr_line, filename));
}

bool	parse(const char *filename, t_minirt *minirt)
{
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		errors(CER_OPEN_FILE, ER_OPEN_FILE, NULL);
	return (read_file(fd, minirt, filename));
}
