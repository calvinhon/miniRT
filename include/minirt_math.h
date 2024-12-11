#ifndef MINIRT_MATH_H
#define MINIRT_MATH_H

#include <math.h>

#define EPISILON 0.00001

typedef struct s_point
{
	double x;
	double y;
	double z;
	double p;
}	t_point;

typedef struct s_vec4d
{
	double x;
	double y;
	double z;
	double p;
}	t_vec4d;

typedef struct s_mat2d
{
	double matrix[2][2];
}	t_mat2d;

typedef struct s_mat3d
{
	double matrix[3][3];
}	t_mat3d;

typedef struct s_mat4d
{
	double matrix[4][4];
}	t_mat4d;

t_point	create_point(double x, double y, double z);
t_point	add_v_to_p(t_point p, t_vec4d v);
t_point	minus_v_from_p(t_point p, t_vec4d v);
t_vec4d	create_vector(double x, double y, double z);
t_vec4d	add_vectors(t_vec4d v1, t_vec4d v2);
t_vec4d	subtract_points(t_point p1, t_point p2);
t_vec4d	scale_vector(t_vec4d v, double factor);
t_vec4d	negate_vector(t_vec4d v);
double	magnitude(t_vec4d v);
t_vec4d	normalize(t_vec4d v);
double	dot(t_vec4d v1, t_vec4d v2);

#endif