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

float fade(float t) {
    return 6 * t * t * t * t * t - 15 * t * t * t * t + 10 * t * t * t;
}

// Linear interpolation
float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

// Gradient calculation
float grad(int hash, float x, float y) {
    // Pseudo-random gradient vectors based on hash
    switch (hash & 3) { // Use last 2 bits of hash
        case 0: return x + y;
        case 1: return -x + y;
        case 2: return x - y;
        case 3: return -x - y;
    }
    return 0; // Should never reach here
}

// Perlin noise calculation for a 2D point
float perlin_noise(float x, float y, float z)
{
    // Grid cell coordinates
    int x0 = floor(x);
    int y0 = floor(y);
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    // Relative position within the cell
    float dx = x - x0;
    float dy = y - y0;

    // Hash the grid corners
    int hash_x0_y0 = hash(x0, y0);
    int hash_x1_y0 = hash(x1, y0);
    int hash_x0_y1 = hash(x0, y1);
    int hash_x1_y1 = hash(x1, y1);

    // Compute gradients at corners
    float g00 = grad(hash_x0_y0, dx, dy);
    float g10 = grad(hash_x1_y0, dx - 1, dy);
    float g01 = grad(hash_x0_y1, dx, dy - 1);
    float g11 = grad(hash_x1_y1, dx - 1, dy - 1);

    // Apply fade function to dx and dy
    float u = fade(dx);
    float v = fade(dy);

    // Interpolate horizontally and vertically
    float nx0 = lerp(g00, g10, u);
    float nx1 = lerp(g01, g11, u);
    float value = lerp(nx0, nx1, v);
	(void)z;
    return value; // Return final noise value
}

t_color	pattern_at(t_object *o, t_point *world_point, t_pattern *pat)
{
	t_point		pat_pt;
	t_color		color;
	float		noise;
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
	color = pat->a;
	pat_pt = mult_mat4d_pt4d(o->inv_transform, *world_point);
	pat_pt = mult_mat4d_pt4d(pat->inv_transform, pat_pt);
	noise = 0;
	if (pat->is_perturbed)
		noise = perlin_noise(pat_pt.x, pat_pt.y, pat_pt.z);
	if ((pat->type == STRIPED && (int)floor(pat_pt.x) % 2)
		|| (pat->type == RING
		&& (int)floor(sqrt(pow(pat_pt.x, 2) + pow(pat_pt.z, 2))) % 2)
		|| (pat->type == CHECKER
		&& (int)(floor(pat_pt.x + EPSILON) + floor(pat_pt.y + EPSILON)
		+ floor(pat_pt.z + EPSILON)) % 2))
			color = pat->b;
	else if (pat->type == GRADIENT)
		color = add_colors(2, pat->a,
			scale_color(subtract_colors(pat->b, pat->a),
			pat_pt.x - floor(pat_pt.x)));
	return (color);
}
