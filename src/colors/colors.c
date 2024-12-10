#include "colors.h"

t_color	create_color(int r, int g, int b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color	add_colors(t_color c1, t_color c2)
{
	return (create_color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b));
}

t_color	subtract_colors(t_color c1, t_color c2)
{
	return (create_color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b));
}

t_color	scale_color(t_color c, int scale)
{
	return (create_color(c.r * scale, c.g * scale, c.b * scale));
}

t_color	multiply_colors(t_color c1, t_color c2)
{
	return (create_color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b));
}
