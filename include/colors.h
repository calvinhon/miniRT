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

# define WHITE 0xFFFFFF
# define GOLD 0xFFD700
# define OLIVE 0x808000
# define LIME 0x32CD32
# define PURPLE 0x800080

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

t_color	create_color(int r, int g, int b);
t_color	add_colors(t_color c1, t_color c2);
t_color	subtract_colors(t_color c1, t_color c2);
t_color	scale_color(t_color c, int scale);
t_color	multiply_colors(t_color c1, t_color c2);
int		plot_color(t_color c);

#endif