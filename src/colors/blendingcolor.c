#include "../include/minirt.h"

t_color calculate_diffuse(t_vec4d normal, t_vec4d light_dir, t_color object_color, t_color light_color, float intensity)
{
	float diff_factor = fmax(0.0f, vec4d_dot(normal, light_dir));
	t_color blended_color = color_multiply(object_color, light_color);
	return color_scale(blended_color, diff_factor * intensity);
}
