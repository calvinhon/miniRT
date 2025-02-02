#include "minirt.h"

t_vec4d get_normal_from_texture(t_frame *bump_map, float u, float v)
{
    uint32_t	color;
	int			x;
	int			y;
	t_color		c;
    t_vec4d 	normal;

	x = (int)(u * bump_map->tex_width) % bump_map->tex_width;
	y = (int)(v * bump_map->tex_height) % bump_map->tex_height;
	// printf("%d %d\n", x, y);
	color = bump_map->addr[y * bump_map->tex_width + x];
    c.r = (int)((color >> 16) & 0xFF);
    c.g = (int)((color >> 8) & 0xFF);
    c.b = (int)(color & 0xFF);
    normal.x = (c.r / 255.0) * 2.0 - 1.0;
    normal.y = (c.g / 255.0) * 2.0 - 1.0;
    normal.z = (c.b / 255.0) * 2.0 - 1.0;
    return (normal);
}

t_vec4d apply_normal_mapping(t_point *wrld_p, t_frame *bump_map)
{
    float	u;
	float	v;

	u = fmod(wrld_p->x, 1.0);
    v = fmod(wrld_p->y, 1.0);
    if (u < 0)
		u += 1.0;
    if (v < 0)
		v += 1.0;
	return (get_normal_from_texture(bump_map, u, v));
}
