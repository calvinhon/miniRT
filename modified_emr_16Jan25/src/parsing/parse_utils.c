/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:22:29 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 18:40:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool	parse_vec4p(t_vec4s *vec, char *str, t_minirt *minirt, int curr_line)
{
	t_split	split;

	split = ft_split(str, ",");
	if (split.wordcount != 3)
		return (parse_err_msg(ER_VEC4_FORMAT, ER_EXPECT_TUPLE, curr_line),
			false);
	vec->x = ft_atof(split.array[0], minirt);
	if (minirt->error_code == 2)
		return (parse_err_msg(ER_FLOAT_VALUE, ER_EXPECT_FLOAT, curr_line),
			false);
	vec->y = ft_atof(split.array[1], minirt);
	if (minirt->error_code == 2)
		return (parse_err_msg(ER_FLOAT_VALUE, ER_EXPECT_FLOAT, curr_line),
			false);
	vec->z = ft_atof(split.array[2], minirt);
	if (minirt->error_code == 2)
		return (parse_err_msg(ER_FLOAT_VALUE, ER_EXPECT_FLOAT, curr_line),
			false);
	vec->w = 1.0f;
	return (destroy_2d_arr(split.array), true);
}

bool	parse_vec4v(t_vec4s *vec, char *str, t_minirt *minirt, int curr_line)
{
	t_split	split;

	split = ft_split(str, ",");
	if (split.wordcount != 3)
		return (parse_err_msg(ER_VEC4_FORMAT, ER_EXPECT_TUPLE, curr_line),
			false);
	vec->x = ft_atof(split.array[0], minirt);
	if (minirt->error_code == 2)
		return (parse_err_msg(ER_FLOAT_VALUE, ER_EXPECT_FLOAT, curr_line),
			false);
	vec->y = ft_atof(split.array[1], minirt);
	if (minirt->error_code == 2)
		return (parse_err_msg(ER_FLOAT_VALUE, ER_EXPECT_FLOAT, curr_line),
			false);
	vec->z = ft_atof(split.array[2], minirt);
	if (minirt->error_code == 2)
		return (parse_err_msg(ER_FLOAT_VALUE, ER_EXPECT_FLOAT, curr_line),
			false);
	vec->w = 0.0f;
	return (destroy_2d_arr(split.array), true);
}

bool	parse_single_f(float *f, char *str, t_minirt *minirt, int curr_line)
{
	*f = ft_atof(str, minirt);
	if (minirt->error_code == 2)
		return (parse_err_msg(ER_OBJ_VALUE, ER_EXPECT_FLOAT, curr_line),
			false);
	return (true);
}

bool	check_final_color_range(t_color *color, int curr_line)
{
	if (color->r < 0.0f || color->g < 0.0f || color->b < 0.0f
		|| color->r > 1.0f || color->g > 1.0f || color->b > 1.0f)
		return (parse_err_msg(ER_COLOR_VALUE, ER_EXPECT_COLOR_RANGE,
				curr_line), false);
	color->a = (OS_MACOS == 0);
	return (true);
}

bool	parse_color(t_color *color, char *str, int curr_line)
{
	t_split	split;
	t_eint	color_int;

	split = ft_split(str, ",\n\r");
	if (split.wordcount != 3)
		return (parse_err_msg(ER_COLOR_FORMAT, ER_EXPECT_COLOR_FORMAT,
				curr_line), false);
	color_int = ft_atoi(split.array[0]);
	if (color_int.error)
		return (parse_err_msg(ER_COLOR_VALUE, ER_EXPECT_INT,
				curr_line), false);
	color->r = color_int.value / 255.999;
	color_int = ft_atoi(split.array[1]);
	if (color_int.error)
		return (parse_err_msg(ER_COLOR_VALUE, ER_EXPECT_INT,
				curr_line), false);
	color->g = color_int.value / 255.999;
	color_int = ft_atoi(split.array[2]);
	if (color_int.error)
		return (parse_err_msg(ER_COLOR_VALUE, ER_EXPECT_INT,
				curr_line), false);
	color->b = color_int.value / 255.999;
	if (!check_final_color_range(color, curr_line))
		return (destroy_2d_arr(split.array), false);
	return (destroy_2d_arr(split.array), true);
}
