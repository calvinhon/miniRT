/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:54:07 by marvin            #+#    #+#             */
/*   Updated: 2024/12/11 16:54:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MATH_H
# define MINIRT_MATH_H

# include <stdbool.h>
# include <math.h>
# include <stdarg.h>
# include <stdio.h>

# define EPSILON 0.0001f

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	float	p;
}	t_point;

typedef struct s_vec2d
{
	float	x;
	float	y;
}	t_vec2d;

typedef struct s_vec3d
{
	float	x;
	float	y;
	float	z;
}	t_vec3d;

typedef struct s_vec4d
{
	float	x;
	float	y;
	float	z;
	float	p;
}	t_vec4d;

typedef struct s_shear
{
	float	x_y;
	float	x_z;
	float	y_x;
	float	y_z;
	float	z_x;
	float	z_y;
}	t_shear;

typedef struct s_mat2d
{
	float	matrix[4];
}	t_mat2d;

typedef struct s_mat3d
{
	float	matrix[9];
}	t_mat3d;

typedef struct s_mat4d
{
	float	matrix[16];
}	t_mat4d;

typedef struct s_idx
{
	int		count;
	int		i;
	int		j;
	t_mat4d	*m1;
	t_mat4d	*m2;
}	t_idx;

/*--- POINTS ---*/
t_point	create_point(float x, float y, float z);
t_point	add_v_to_p(const t_point *p, t_vec4d *v);
t_point	subtract_v_from_p(const t_point *p, const t_vec4d *v);
t_point	mult_mat4d_pt4d(const t_mat4d *m, const t_point *p);

/*--- VECTORS ---*/
t_vec4d	create_vec4d(float x, float y, float z);
t_vec4d	add_vectors(const t_vec4d *v1, const t_vec4d *v2);
t_vec4d	subtract_points(t_point *p1, t_point *p2);
t_vec4d	subtract_vectors(const t_vec4d *v1, const t_vec4d *v2);
t_vec4d	subtract_vectors_val(const t_vec4d v1, const t_vec4d v2);
void	scale_vector(t_vec4d *out, const t_vec4d *v, float factor);
t_vec4d	scale_vector_re(const t_vec4d *v, float factor);
t_vec4d	negate_vector(const t_vec4d *v);
t_vec4d	normalize(const t_vec4d *v);
void	normalize_vec4d(t_vec4d *v);
t_vec4d	cross_pointers(const t_vec4d *v1, const t_vec4d *v2);
t_vec4d	cross_values(t_vec4d v1, t_vec4d v2);
t_vec4d	row(const t_mat4d *m, int i);
t_vec4d	col(const t_mat4d *m, int i);

/*--- FLOATS ---*/
float	magnitude(const t_vec4d *v);
float	dot_v_p(t_vec4d v, const t_point *p);
float	dot_pointers(const t_vec4d *v1, const t_vec4d *v2);
float	dot_values(t_vec4d v1, t_vec4d v2);

/*--- MATRICES ---*/
void	fill_row(t_mat4d *m, int row, t_vec4d v);
t_mat4d	fill_matrix(t_vec4d v1, t_vec4d v2, t_vec4d v3, t_vec4d v4);
t_mat4d	mult_n_mat4d(int num_of_matrices, ...);
t_vec4d	mult_mat4d_vec4d(const t_mat4d *m, const t_vec4d *v);
t_mat4d	transpose_mat4d(const t_mat4d *m);
float	determinant_mat2d(const t_mat2d *m);
float	determinant_mat3d(t_mat3d m);
float	determinant_mat4d(const t_mat4d *m);
t_mat2d	submatrix_mat3d(const t_mat3d *m, int row, int col);
t_mat3d	submatrix_mat4d(const t_mat4d *m, int row, int col);
float	minor_mat3d(const t_mat3d *m, int row, int col);
float	cofactor_mat3d(const t_mat3d *m, int row, int col);

/*--- OBJECT MANIPULATION ---*/
t_mat4d	get_inv_tranform_mat4d(const t_mat4d rot, const t_vec4d s, \
	const t_point t);
//t_mat4d	inverse_mat4d(const t_mat4d *m);
t_mat4d	identity_mat(void);
t_mat4d	translation_mat(float x, float y, float z);
t_mat4d	scaling_mat(float x, float y, float z);
t_mat4d	rotate_mat_x(float rad);
t_mat4d	rotate_mat_y(float rad);
t_mat4d	rotate_mat_z(float rad);
t_mat4d	shear_mat(t_shear s);

#endif