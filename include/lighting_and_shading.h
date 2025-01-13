#include "minirt_math.h"
#include "colors.h"

t_vec4d	normal_at(t_object *o, t_point *wrld_p);
t_vec4d	reflect(t_vec4d *in, t_vec4d *normal);
t_color	lighting(t_object *o, t_light *l, t_point *p, t_vec4d *eye_v, t_vec4d *normal_v);
