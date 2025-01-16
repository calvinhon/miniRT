/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:54:55 by chon              #+#    #+#             */
/*   Updated: 2024/12/11 15:54:55 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "structs.h"
# include <stdarg.h>
# include <math.h>

t_color			create_color(float r, float g, float b);
t_color			add_colors(int num_of_colors, ...);
t_color			subtract_colors(t_color c1, t_color c2);
t_color			scale_color(t_color c, float scale);
t_color			mult_colors(t_color c1, t_color c2);
unsigned int	plot_color(t_color c);

#endif