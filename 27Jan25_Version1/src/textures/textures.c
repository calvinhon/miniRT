/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:09:35 by nth          #+#    #+#             */
/*   Updated: 2024/11/18 17:05:50 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

t_color	rt_sample_texture(const t_frame *fra_tex, const t_vec2s *uv)
{
	int			tex_x;
	int			tex_y;
	char		*src;
	uint32_t	color_value;
	t_color		retval;

	tex_x = floorf((int)(uv->x * fra_tex->tex_width) % fra_tex->tex_width);
	tex_y = floorf((int)(uv->y * fra_tex->tex_height) % fra_tex->tex_height);
	src = fra_tex->addr + (tex_y * fra_tex->line_length + \
		tex_x * fra_tex->bpp_8);
	color_value = *(uint32_t *)src;
	retval.r = (color_value >> 16) & 0xFF;
	retval.g = (color_value >> 8) & 0xFF;
	retval.b = color_value & 0xFF;
	scale_vec4s(&retval.v, retval.v, 1.f / 255.999f);
	retval.a = (OS_MACOS == 0);
	return (retval);
}

static inline t_vec4s	_from_sample_to_tangent_normal(const t_color *sample)
{
	t_vec4s	tangent_normal;

	vec4sp_ini(&tangent_normal, sample->r, sample->g, sample->b);
	scale_vec4s(&tangent_normal, tangent_normal, 2.f);
	tangent_normal = sub_vec4s_re(tangent_normal, vec4sp_re(1.f, 1.f, 1.f));
	tangent_normal.a[3] = 0.f;
	tangent_normal.w = 0.f;
	return (tangent_normal);
}

static inline t_mat4s	_construct_tbn_matrix(const t_vec4s *local_normal,
							const t_vec4s *tangent, const t_vec4s *bitangent)
{
	t_mat4s	retval;

	retval.r1 = vec4sv_re(tangent->x, bitangent->x, local_normal->x);
	retval.r2 = vec4sv_re(tangent->y, bitangent->y, local_normal->y);
	retval.r3 = vec4sv_re(tangent->z, bitangent->z, local_normal->z);
	retval.r4 = vec4sp_re(0, 0, 0);
	return (retval);
}

t_vec4s	rt_apply_normal_map(const t_object *obj, const t_vec2s *uv,
			const t_vec4s *local_normal, const t_vec4s *tangent)
{
	const t_color	sample = rt_sample_texture(obj->material.fra_tex, uv);
	t_vec4s			tangent_normal;
	t_vec4s			bitangent;
	t_mat4s			tbn_matrix;
	t_vec4s			perturbed_normal;

	cross_vec4s(&bitangent, *local_normal, *tangent);
	tangent_normal = _from_sample_to_tangent_normal(&sample);
	negate_vec4s(&bitangent);
	normalize_vec4s(&bitangent);
	tbn_matrix = _construct_tbn_matrix(local_normal, tangent, &bitangent);
	cross_mat4s_vec4s(&tbn_matrix, &tangent_normal, &perturbed_normal);
	normalize_vec4s(&perturbed_normal);
	return (perturbed_normal);
}
