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
#define COLORS_H

#include "miniRT.h"

#define WHITE 0xFFFFFF
#define GOLD 0xFFD700
#define OLIVE 0x808000
#define LIME 0x32CD32
#define PURPLE 0x800080
#define BLACK 0x000000

t_color create_color(float r, float g, float b);
t_color add_colors(int num_of_colors, ...);
t_color subtract_colors(const t_color *c1, const t_color *c2);
t_color scale_color(const t_color *c, float scale);
t_color mult_colors(const t_color *c1, const t_color *c2);
t_color	normalize_color(t_color c);
unsigned int plot_color(t_color *c);

#endif