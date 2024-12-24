/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:54:07 by marvin            #+#    #+#             */
/*   Updated: 2024/12/11 16:54:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MATH_H
#define MINIRT_MATH_H

# include <math.h>
# include "structs.h"

#define EPISILON 0.00001

t_point	create_point(double x, double y, double z);
t_point	add_v_to_p(t_point p, t_vec4d v);
t_point	minus_v_from_p(t_point p, t_vec4d v);
double	dot_v_p(t_vec4d v, t_point p);
t_point	mult_mat4d_pt4d(t_mat4d m, t_point p);
t_vec2d	create_vec2d(double x, double y);
t_vec3d	create_vec3d(double x, double y, double z);
t_vec4d	create_vec4d(double x, double y, double z);
t_vec4d	add_vectors(t_vec4d v1, t_vec4d v2);
t_vec4d	subtract_points(t_point p1, t_point p2);
t_vec4d	scale_vector(t_vec4d v, double factor);
t_vec4d	negate_vector(t_vec4d v);
double	magnitude(t_vec4d v);
t_vec4d	normalize(t_vec4d v);
double	dot(t_vec4d v1, t_vec4d v2);
t_mat2d	create_mat2d(t_vec2d v1, t_vec2d v2);
t_mat3d	create_mat3d(t_vec3d v1, t_vec3d v2, t_vec3d v3);
t_mat4d	create_mat4d(t_vec4d v1, t_vec4d v2, t_vec4d v3, t_vec4d v4);
t_vec4d	row(t_mat4d m, int i);
t_vec4d	col(t_mat4d m, int i);
bool	is_equal_mat4d(t_mat4d m1, t_mat4d m2);
t_mat4d	mult_2x_mat4d(t_mat4d m1, t_mat4d m2);
t_vec4d	mult_mat4d_vec4d(t_mat4d m, t_vec4d v);
t_mat4d	transpose_mat4d(t_mat4d m);
double	determinant_mat2d(t_mat2d m);
double	determinant_mat3d(t_mat3d m);
double	determinant_mat4d(t_mat4d m);
t_mat2d	submatrix_mat3d(t_mat3d m, int row, int col);
t_mat3d	submatrix_mat4d(t_mat4d m, int row, int col);
double	minor_mat3d(t_mat3d m, int row, int col);
double	cofactor_mat3d(t_mat3d m, int row, int col);
t_mat4d	inverse_mat4d(t_mat4d m);
t_mat4d	identity_mat(void);
t_mat4d	translation_mat(double x, double y, double z);
t_mat4d	scaling_mat(double x, double y, double z);
t_mat4d	rotate_mat_x(double rad);
t_mat4d	rotate_mat_y(double rad);
t_mat4d	rotate_mat_z(double rad);
t_mat4d	shear_mat(t_shear s);

#endif