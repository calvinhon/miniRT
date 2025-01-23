/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lag.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 06:33:18 by nth          #+#    #+#             */
/*   Updated: 2024/11/18 10:52:31 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAG_H
# define LAG_H

# include "ltypes.h" // for SSE/AVX(2) instrinsics and Lag types
# include <math.h>

/*--- INIT_PS ---*/

/// @brief Returns a `t_vec4s` with components (x, y, z, w)
t_vec4s	vec4s_re(float x, float y, float z, float w);

/// @brief Initialises a `t_vec4s` in homogenous coordinates with a w of `1`
void	vec4sp_ini(t_vec4s *target, float x, float y,
			float z);

/// @brief Returns a `t_vec4s` in homogenous coordinates with a w of `1`
t_vec4s	vec4sp_re(float x, float y, float z);

/// @brief Initialises a `t_vec4s` in homogenous coordinates with a w of `0`
void	vec4sv_ini(t_vec4s *target, float x, float y,
			float z);

/// @brief Returns a `t_vec4s` in homogenous coordinates with a w of `0`
t_vec4s	vec4sv_re(float x, float y, float z);

/*--- LINEAR_ALGEBRA ---*/

/// @brief Performs component-wise (vector) addition and stores the result
///        in the vector pointed-to by `out`.
/// @minirt in1, in2 operand
/// @minirt out Pointer to the vector that stores the result.
void	add_vec4s(t_vec4s *out, const t_vec4s *in1,
			const t_vec4s *in2);

/// @brief Performs component-wise (vector) addition.
t_vec4s	add_vec4s_re(const t_vec4s in1, const t_vec4s in2);

/// @brief Performs component-wise (vector) subtraction and stores the result
///        in the vector pointed-to by `out`.
/// @minirt in1, in2 operand
/// @minirt out Pointer to the vector that stores the result.
void	sub_vec4s(t_vec4s *out, const t_vec4s *in1,
			const t_vec4s *in2);

/// @brief Performs component-wise (vector) subtraction.
t_vec4s	sub_vec4s_re(const t_vec4s in1, const t_vec4s in2);

/// @brief Scales a vector by a scalar and stores the result in the vector
///        pointed-to by `out`.
/// @minirt in Vector to be scaled
/// @minirt scalar Scalar to scale the vector by
void	scale_vec4s(t_vec4s *out, const t_vec4s in,
			float scalar);

/// @brief Scales a vector by a scalar.
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
t_vec4s	scale_vec4s_re(const t_vec4s in, float scalar);

/// @brief Negates a vector and stores the result
///        in the vector pointed-to by `out`.
/// @minirt in Vector to be negated
/// @minirt out Pointer to the vector that stores the result.
void	negate_vec4s_new(t_vec4s *out, const t_vec4s in);

/// @brief Negates a vector in place.
/// @minirt target Pointer to vector to be negated
void	negate_vec4s(t_vec4s *target);

/// @brief Negates a vector.
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
t_vec4s	negate_vec4s_re(const t_vec4s in);

/// @brief Calculates the dot product of two `t_vec4s`, and stores the result
///        in the variable pointed-to by `out`.
/// @minirt out Pointer to the variable that stores the result.
/// @minirt in1 Vector to calculate the dot product of
/// @minirt in2 Vector to calculate the dot product of
void	dot_vec4s(float *out, const t_vec4s *in1,
			const t_vec4s *in2);

/// @brief Calculates the dot product of two `t_vec4s`.
float	dot_vec4s_re(const t_vec4s *in1,
			const t_vec4s *in2);

/// @brief Calculates the magnitude of a `t_vec4s` and stores the result
///        in the variable pointed-to by `out`.
/// @minirt in Vector to calculate the magnitude of
/// @minirt out Pointer to the variable that stores the result.
void	magnitude_vec4s(float *out, const t_vec4s in);

/// @brief Calculates the magnitude of a `t_vec4s`.
float	magnitude_vec4s_re(const t_vec4s in);

/// @brief Calculates the cross product of two `t_vec4s`
///        (ignoring the `w` component) and stores the result
///        in the vector pointed-to by `out`.
/// @minirt in1, in2 operand
/// @minirt out Pointer to the vector that stores the result.
void	cross_vec4s(t_vec4s *out, const t_vec4s in1,
			const t_vec4s in2);

/// @brief Calculates the cross product of two `t_vec4s`
///        (ignoring the w component).
t_vec4s	cross_vec4s_re(const t_vec4s in1,
			const t_vec4s in2);

/// @brief Checks equality of `a` and `b` within a set `tolerance`.
///        `__FLT_EPSILON__` or a value slightly higher works.
/// @minirt a, b `t_vec4s` vector
/// @minirt tolerance Desired tolerance.
/// @return `true (1)` or `false (0)`, depending on the comparison result.
/// @warning If either of the values entered contain `NaN`, the result
///          will be `false (0)`.
bool	equal_vec4s(const t_vec4s a, const t_vec4s b,
			float tolerance);

/// @brief Checks EXACT equality of `a` and `b`. Use wisely.
/// @minirt a, b `t_vec4s` vector
/// @return `true (1)` or `false (0)`, depending on the comparison result.
/// @warning If either of the values entered contain `NaN`, the result
///          will be `false (0)`.
bool	precequal_vec4s(const t_vec4s a, const t_vec4s b);

/// @brief Normalizes a `t_vec4s` in place.
/// @minirt target Pointer to `t_vec4s` to be normalized
/// @warning Recommend using an EPSILON of around `0.0001`.
///          For better precision, use `normalize_vec4s_medp`.
///          For highest precision, use `normalize_vec4s_highp`.
void	normalize_vec4s(t_vec4s *target);

/// @brief Returns a normalized version of the `t_vec4s`: `in`.
/// @minirt in `t_vec4s` to be normalized.
/// @warning Recommend using an EPSILON of around `0.0001`.
///          For better precision, use `normalize_vec4s_medp`.
///          For highest precision, use `normalize_vec4s_highp`.
t_vec4s	normalize_vec4s_re(const t_vec4s in);

/// @brief Normalizes a `t_vec4s` and stores the result
///        in the `t_vec4s` pointed-to by `out`.
/// @minirt out Pointer to the `t_vec4s` that stores the result.
/// @minirt in `t_vec4s` to be normalized.
/// @warning Recommend using an EPSILON of around `0.0001`.
///          For better precision, use `normalize_vec4s_medp`.
///          For highest precision, use `normalize_vec4s_highp`.
void	normalize_vec4s_new(t_vec4s *out, const t_vec4s in);

/// @brief Returns a `t_mat4s` using the parameters as its rows.
t_mat4s	inirows_mat4s_re(const t_vec4s r1, const t_vec4s r2,
			const t_vec4s r3, const t_vec4s r4);

/// @brief Returns a `t_mat4s` identity matrix.
t_mat4s	ini_indentity_mat4s(void);

/// @brief Returns a `t_mat4s` affine translation-matrix
///        (`r4 = {0, 0, 0, 1}`).
t_mat4s	translation_mat4s(float tx, float ty, float tz);

/// @brief Returns a `t_mat4s` affine scaling-matrix.
///        (`r4 = {0, 0, 0, 1}`).
t_mat4s	scaling_mat4s(float sx, float sy, float sz);

/// @brief Returns a rotation matrix around the x-axis.
/// @minirt rad Rotation in radians
t_mat4s	rotatex_mat4s(float rad);

/// @brief Returns a rotation matrix around the y-axis.
/// @minirt rad Rotation in radians
t_mat4s	rotatey_mat4s(float rad);

/// @brief Returns a rotation matrix around the z-axis.
/// @minirt rad Rotation in radians
t_mat4s	rotatez_mat4s(float rad);

/// @brief Returns the cross product of a `t_mat4s` with a `t_vec4s`
///        (in that order).
void	cross_mat4s_vec4s(const t_mat4s *m,
			const t_vec4s *v, t_vec4s *out);

/// @brief computes the cross product of `in1` with `in2`
///        (in that order), and stores the result in the `t_mat4s`
///        pointed-to by `out`.
void	cross_mat4s_mat4s(const t_mat4s in1,
			const t_mat4s in2, t_mat4s *out);

/// @brief Calculates the inverse of a decomposed matrix
/// (rotation, scale, translation)
/// @minirt rot The rotational component of the matrix
/// @minirt s The scale factor of the matrix
/// @minirt t The translation component of the matrix
/// @return The inverse of the decomposed matrix
/// @warning The scale should NOT contain any zero components as that will
/// cause a floating-point exception.
//t_mat4s	get_inv_tranform_mat4s(const t_mat4s rot, const __m128 s,
//			const __m128 t);
t_mat4s get_inv_tranform_mat4s(const t_mat4s rot, const t_vec4s s, const t_vec4s t);

/*--- PS_EXTRA ---*/

/// @brief Returns a normalized version of the `t_vec4s`: `in`.
/// @minirt in `t_vec4s` to be normalized.
t_vec4s	normalize_vec4s_medp(const t_vec4s in);

/// @brief Returns a normalized version of the `t_vec4s`: `in`.
/// @minirt in `t_vec4s` to be normalized.
t_vec4s	normalize_vec4s_highp(const t_vec4s in);

#endif // !LAG_H