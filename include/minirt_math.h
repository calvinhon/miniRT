#ifndef MINIRT_MATH_H
# define MINIRT_MATH_H

# include <math.h>

# define EPISILON 0.00001

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	double	p;
}	t_point;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
	double	p;
}	t_vector;

t_point		create_point(double x, double y, double z);
t_point		add_v_to_p(t_point p, t_vector v);
t_point		minus_v_from_p(t_point p, t_vector v);
t_vector	create_vector(double x, double y, double z);
t_vector	add_vectors(t_vector v1, t_vector v2);
t_vector	subtract_points(t_point p1, t_point p2);
t_vector	scale_vector(t_vector v, double factor);
t_vector	negate_vector(t_vector v);
double		magnitude(t_vector v);
t_vector	normalize(t_vector v);
double		dot(t_vector v1, t_vector v2);

#endif