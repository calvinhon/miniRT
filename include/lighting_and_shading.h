#include "minirt_math.h"
#include "colors.h"

t_vec4d	sphere_normal_at(t_object *o, t_point *wrld_p);
t_vec4d	reflect(t_vec4d *in, t_vec4d *normal);
t_color	lighting(t_material *material, t_light *l, t_comps *c);
t_color	shade_hit(t_scene *s, t_comps *comps, int depth);
