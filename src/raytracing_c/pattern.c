/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:12:10 by chon              #+#    #+#             */
/*   Updated: 2025/01/16 17:12:16 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	fade(float t)
{
    return (6 * pow(t, 5) - 15 * pow(t, 4) + 10 * pow(t, 3));
}

float lerp(float a, float b, float t)
{
    return (a + t * (b - a));
}

float	grad(int hash, float x, float y, float z)
{
	int		h; 
	double	u;
	double	v;

	h = hash & 15;
	if (h < 8)
		u = x;
	else
		u = y;
	if (h < 4)
		v = y;
	else if (h == 12 || h == 14)
		v = x;
	else
		v = z;
	if ((h & 1))
		u = -u;
	if ((h & 2))
		v = -v;
	return (u + v);
}

float	perlin_noise(float x, float y, float z)
{
	t_perturbed	p;
	static int	permutation[256] = {151,160,137,91,90,15,131,13,201,95,96,53,
		194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,190,6,148,247,
		120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,88,237,
		149,56,87,174,20,125,136,171,168,68,175,74,165,71,134,139,48,27,166,
		77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,
		40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208,89,18,
		169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,
		226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,
		58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,
		101,155,167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,
		112,104,218,246,97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,
		51,145,235,249,14,239,107,49,192,214,31,181,199,106,157,184,84,204,176,
		115,121,50,45,127,4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,
		128,195,78,66,215,61,156,180};

	p.i = (int)floor(x) & 255;
	p.j = (int)floor(y) & 255;
	p.k = (int)floor(z) & 255;
	p.u = fade(x - floor(x));
	p.v = fade(y - floor(y));
	p.w = fade(z - floor(z));
	p.a = permutation[p.i] + p.j;
	p.aa = permutation[p.a] + p.k;
	p.ab = permutation[p.a + 1] + p.k;
	p.b = permutation[p.i + 1] + p.j;
	p.ba = permutation[p.b] + p.k;
	p.bb = permutation[p.b + 1] + p.k;
	p.gradaa = grad(permutation[p.aa], x, y, z);
	p.gradab = grad(permutation[p.ab], x, y, z - 1);
	p.gradba = grad(permutation[p.ba], x - 1, y, z);
	p.gradbb = grad(permutation[p.bb], x - 1, y, z - 1);
	p.gradaa1 = grad(permutation[p.aa + 1], x, y + 1, z);
    p.gradab1 = grad(permutation[p.ab + 1], x, y + 1, z - 1);
    p.gradba1 = grad(permutation[p.ba + 1], x - 1, y + 1, z);
    p.gradbb1 = grad(permutation[p.bb + 1], x - 1, y + 1, z - 1);
	p.x1 = lerp(p.w, p.gradaa, p.gradab);
	p.x2 = lerp(p.w, p.gradba, p.gradbb);
	p.x3 = lerp(p.w, p.gradaa1, p.gradab1);
    p.x4 = lerp(p.w, p.gradba1, p.gradbb1);
	p.y1 = lerp(p.v, p.x1, p.x2);
	p.y2 = lerp(p.v, p.x3, p.x4);
	return (lerp(p.u, p.y1, p.y2));
}

t_color	pattern_at(t_object *o, t_point *world_point, t_pattern *pat)
{
	t_point		pat_pt;
	t_color		color;
	float		noise;

	color = pat->a;
	pat_pt = mult_mat4d_pt4d(o->inv_transform, *world_point);
	pat_pt = mult_mat4d_pt4d(pat->inv_transform, pat_pt);
	noise = 0;
	if (pat->is_perturbed)
		noise = perlin_noise(pat_pt.x, pat_pt.y, pat_pt.z) * pat->p_scale;
	if ((pat->type == STRIPED && (int)floor(pat_pt.x + noise) % 2)
		|| (pat->type == RING
		&& (int)floor(sqrt(pow(pat_pt.x, 2) + pow(pat_pt.z, 2)) + noise) % 2)
		|| (pat->type == CHECKER
		&& (int)(floor(pat_pt.x + EPSILON + noise) + floor(pat_pt.y + EPSILON + noise)
		+ floor(pat_pt.z + EPSILON + noise)) % 2))
			color = pat->b;
	else if (pat->type == GRADIENT)
		color = add_colors(2, pat->a,
			scale_color(subtract_colors(pat->b, pat->a),
			noise + (pat_pt.x - floor(pat_pt.x))));
	return (color);
}
