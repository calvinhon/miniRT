#include "minirt_math.h"
#include "colors.h"

t_vec4d	normal_at(t_sphere s, t_point wrld_p);
t_vec4d	reflect(t_vec4d in, t_vec4d normal);
t_color	lighting(t_sphere s, t_light l, t_point p, t_vec4d eye_v);