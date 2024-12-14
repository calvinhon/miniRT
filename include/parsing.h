/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:07:24 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/14 19:50:06 by honguyen         ###   ########.fr       */
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
#endif