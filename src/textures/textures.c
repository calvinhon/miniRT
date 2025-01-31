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

#include "minirt.h"
#include "macros.h"

t_color rt_sample_texture(const t_frame *fra_tex, const t_vec2d *uv)
{
	int tex_x;
	int tex_y;
	char *src;
	uint32_t color_value;
	t_color retval;

	tex_x = floorf((int)(uv->x * fra_tex->tex_width) % fra_tex->tex_width);
	tex_y = floorf((int)(uv->y * fra_tex->tex_height) % fra_tex->tex_height);
	src = fra_tex->addr + (tex_y * fra_tex->line_length + tex_x * fra_tex->bpp_8);
	color_value = *(uint32_t *)src;
	retval.r = (color_value >> 16) & 0xFF;
	retval.g = (color_value >> 8) & 0xFF;
	retval.b = color_value & 0xFF;
	//scale_vector(&retval.v, retval.v, 1.f / 255.999f);
	retval.a = (OS_MACOS == 0);
	return (retval);
}

static inline t_vec4d _from_sample_to_tangent_normal(const t_color *sample)
{
	t_vec4d tangent_normal;
	t_vec4d unit_v;

	tangent_normal = create_vec4d(sample->r, sample->g, sample->b);
	scale_vector(&tangent_normal, &tangent_normal, 2.f);
	unit_v = create_vec4d(1.f, 1.f, 1.f);
	tangent_normal = subtract_vectors(&tangent_normal, &unit_v);
	// tangent_normal.a[3] = 0.f;
	return (tangent_normal);
}

static inline t_mat4d _construct_tbn_matrix(const t_vec4d *local_normal,
											const t_vec4d *tangent, const t_vec4d *bitangent)
{
	t_mat4d m;

	fill_row(&m, 0, create_vec4d(tangent->x, bitangent->x, local_normal->x));
	fill_row(&m, 1, create_vec4d(tangent->y, bitangent->y, local_normal->y));
	fill_row(&m, 2, create_vec4d(tangent->z, bitangent->z, local_normal->z));
	fill_row(&m, 3, create_vec4d(0, 0, 0));
	return (m);
}

t_vec4d rt_apply_normal_map(const t_object *obj, const t_vec2d *uv,
							const t_vec4d *local_normal, const t_vec4d *tangent)
{
	const t_color sample = rt_sample_texture(obj->material.fra_tex, uv);
	t_vec4d tangent_normal;
	t_vec4d bitangent;
	t_mat4d tbn_matrix;
	t_vec4d perturbed_normal;

	bitangent = cross_pointers(local_normal, tangent);
	tangent_normal = _from_sample_to_tangent_normal(&sample);
	bitangent = negate_vector(&bitangent);
	bitangent = normalize(&bitangent);
	tbn_matrix = _construct_tbn_matrix(local_normal, tangent, &bitangent);
	perturbed_normal = mult_mat4d_vec4d(&tbn_matrix, &tangent_normal);
	return (normalize(&perturbed_normal));
}
