#ifndef COLORS_H
# define COLORS_H

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

t_color	create_color(int r, int g, int b);
t_color	add_colors(t_color c1, t_color c2);
t_color	subtract_colors(t_color c1, t_color c2);
t_color	scale_color(t_color c, int scale);
t_color	multiply_colors(t_color c1, t_color c2);

#endif