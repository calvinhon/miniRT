/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:07:24 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/16 19:40:03 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libs/libft/libft.h"
# include "../libs/mlx_linux/mlx.h"
# include "../libs/mlx_macos/mlx.h"
# include "structs.h"
# include "structs.h"

void		errors(int err_code, t_minirt *minirt);
void		check_filename(char *file);
t_minirt	*new_minirt(void);
void		parse(t_minirt *minirt, char *file);
int			add_data(int fd, char *data, size_t *total_size, char *line);
char		*file_data(t_minirt *minirt, size_t *total_size, char *file);

void		parse_data(t_minirt *minirt, char *data);
t_point		parse_point(char *data, size_t *i);
void		parse_light(t_minirt *minirt, char *data, size_t *i);
void		parse_camera(t_minirt *minirt, char *data, size_t *i);
void		parse_ambient(t_minirt *minirt, char *data, size_t *i);
int			parse_int(char *data, size_t *i);
float		parse_float(char *data, size_t *i);
t_point		parse_point(char *data, size_t *i);
t_vector	parse_vector(char *data, size_t *i);
t_color		parse_color(char *data, size_t *i);

#endif