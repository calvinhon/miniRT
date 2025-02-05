/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:48:35 by chon              #+#    #+#             */
/*   Updated: 2025/02/03 10:48:35 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4d	get_bump_normal_from_texture(t_frame *bump_map, float u, float v)
{
	char		*src;
	int			x;
	int			y;
	uint32_t	color;
	t_vec4d		normal;

	x = (int)(u * bump_map->tex_width) % bump_map->tex_width;
	y = (int)(v * bump_map->tex_height) % bump_map->tex_height;
	src = bump_map->addr + (y * bump_map->line_length + x * bump_map->bpp_8);
	color = *(uint32_t *)src;
	normal.x = ((int)((color >> 16) & 0xFF) / 255.0) * 2.0 - 1.0;
	normal.y = ((int)((color >> 8) & 0xFF) / 255.0) * 2.0 - 1.0;
	normal.z = ((int)(color & 0xFF) / 255.0) * 2.0 - 1.0;
	return (normalize(&normal));
}

t_vec4d	get_plane_tangent(t_vec4d *normal)
{
	t_vec4d	tangent;

	if (fabsf(normal->y) < 0.999f)
		tangent = cross_values(create_vec4d(0, 1, 0), *normal);
	else
		tangent = cross_values(create_vec4d(1, 0, 0), *normal);
	return (normalize(&tangent));
}

t_vec4d	apply_bump_map(t_point *obj_p, t_frame *bump_map, t_vec4d *orient_v)
{
	t_vec4d	tangent;
	t_vec4d	bitangent;
	t_vec2d	uv;
	t_vec4d	bump_n;
	t_vec4d	wrld_normal;

	tangent = get_plane_tangent(orient_v);
	bitangent = cross_pointers(orient_v, &tangent);
	bitangent = normalize(&bitangent);
	uv.x = dot_v_p(tangent, obj_p) * 0.1f;
	uv.y = dot_v_p(bitangent, obj_p) * 0.1f;
	uv.x = fmod(uv.x, 1.0);
	uv.y = fmod(uv.y, 1.0);
	if (uv.x < 0)
		uv.x += 1.0;
	if (uv.y < 0)
		uv.y += 1.0;
	bump_n = get_bump_normal_from_texture(bump_map, uv.x, uv.y);
	wrld_normal = create_vec4d(\
		bump_n.x * tangent.x + bump_n.y * bitangent.x + bump_n.z * orient_v->x, \
		bump_n.x * tangent.y + bump_n.y * bitangent.y + bump_n.z * orient_v->y, \
		bump_n.x * tangent.z + bump_n.y * bitangent.z + bump_n.z * orient_v->z);
	return (normalize(&wrld_normal));
}
