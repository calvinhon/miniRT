/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltypes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:13:25 by nth          #+#    #+#             */
/*   Updated: 2024/11/16 20:22:37 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LTYPES_H
# define LTYPES_H

# include <immintrin.h> // For AVX/SSE intrinsics (__m256d, __m128)
# include <stdint.h> // For bit-wise magic (having the option is nice)
# include <stdbool.h> // for `true`, `false`

# ifndef EPSILON
#  define EPSILON 0.0001
# endif // !EPSILON
/*--- VECTOR ---*/

typedef union __attribute((aligned(32))) u_vec4d
{
	float		a[4];
	uint64_t	raw[4];
	struct
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
}	t_vec4d;

typedef union __attribute((aligned(16))) u_vec4s
{
	float		a[4];
	uint32_t	raw[4];
	struct
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
}	t_vec4s;

typedef union u_vec3d
{
	float	a[4];
	struct
	{
		float	x;
		float	y;
		float	z;
		float	ignore;
	};
}__attribute((aligned(32)))	t_vec3d;

typedef union u_vec2s
{
	float	a[2];
	struct
	{
		float	x;
		float	y;
	};
}__attribute((aligned(16)))	t_vec2s;

/*--- MATRIX ---*/

typedef t_vec4d	t_vec4d;

typedef union u_mat2d
{
	float	a[2][2];
	struct
	{
		t_vec2s	r1;
		t_vec2s	r2;
	};
}__attribute((aligned(16)))	t_mat2d;

typedef union u_mat3d
{
	float	a[4][4];
	struct
	{
		t_vec3d	r1;
		t_vec3d	r2;
		t_vec3d	r3;
		t_vec3d	ignore;
	};
}__attribute((aligned(32)))	t_mat3d;

typedef union __attribute((aligned(16))) u_mat4s
{
	float	a[4][4];
	struct
	{
		t_vec4s	r1;
		t_vec4s	r2;
		t_vec4s	r3;
		t_vec4s	r4;
	};
}	t_mat4s;

typedef union u_mat4d
{
	float	a[4][4];
	struct
	{
		t_vec4d	r1;
		t_vec4d	r2;
		t_vec4d	r3;
		t_vec4d	r4;
	};
}__attribute((aligned(32)))	t_mat4d;

typedef t_mat4d	t_mat4d;

#endif