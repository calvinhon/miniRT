/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:36:29 by nth          #+#    #+#             */
/*   Updated: 2024/10/07 02:30:47 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# include "common.h"
# include <stdint.h> // for uint32_t

void		ini_color(t_color *target, float r, float g, float b);
void		add_color(t_color *target, const t_color *c1, const t_color *c2);
void		sub_color(t_color *target, const t_color *c1, const t_color *c2);
void		blend_color(t_color *target, const t_color *c1, const t_color *c2);
void		scale_color(t_color *target, const t_color *c2, float scalar);
void		clamp_color(t_color *color);
uint32_t	convert_color32(const t_color *color);

#endif // !COLORS_H
