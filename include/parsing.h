/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:07:24 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/20 13:57:33 by marvin           ###   ########.fr       */
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
void		allocate_light_obj(t_minirt *minirt);
void		count_elements(t_minirt *minirt, char *line);
void		check_elements(t_minirt *minirt);
size_t		calculate_required_size(char *file, t_minirt *minirt);

char		*file_data(t_minirt *minirt, size_t *total_size, char *file);
void		parse_data(t_minirt *minirt, char *data);
void		parse_light(t_minirt *minirt, char *data, size_t *i);
void		parse_camera(t_minirt *minirt, char *data, size_t *i);
void		parse_ambient(t_minirt *minirt, char *data, size_t *i);


void	parse_object(t_minirt *minirt, char *data, size_t *i);
void	parse_cube(t_minirt *minirt, char *data, size_t *i, size_t idx);
void	parse_cone(t_minirt *minirt, char *data, size_t *i, size_t idx);
void	parse_cylinder(t_minirt *minirt, char *data, size_t *i, size_t idx);
void	parse_sphere(t_minirt *minirt, char *data, size_t *i, size_t idx);
void	parse_plane(t_minirt *minirt, char *data, size_t *i, size_t idx);
void	*allocate_obj(t_minirt *minirt, t_objtype type, size_t idx);


int			parse_int(char *data, size_t *i);
float		parse_float(char *data, size_t *i);
t_point		parse_point(char *data, size_t *i);
t_vec4d		parse_vector(char *data, size_t *i);
t_color		parse_color(char *data, size_t *i);

float		ft_atof(const char *str);

#endif