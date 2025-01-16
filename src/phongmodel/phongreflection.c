#include "structs.h"
#include <math.h>

static t_vec4d vec4d_sub(t_vec4d a, t_vec4d b)
{
	return (t_vec4d){a.x - b.x, a.y - b.y, a.z - b.z, 0.0f};
}

static t_vec4d vec4d_normalize(t_vec4d v)
{
	float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return (t_vec4d){v.x / length, v.y / length, v.z / length, 0.0f};
}

static float vec4d_dot(t_vec4d a, t_vec4d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

static t_vec4d vec4d_scale(t_vec4d v, float scale)
{
	return (t_vec4d){v.x * scale, v.y * scale, v.z * scale, 0.0f};
}

static t_vec4d vec4d_reflect(t_vec4d L, t_vec4d N)
{
	return vec4d_sub(vec4d_scale(N, 2 * vec4d_dot(N, L)), L);
}

static t_color color_scale(t_color color, float factor)
{
	return (t_color){
		.t = color.t,
		.r = (int)(color.r * factor),
		.g = (int)(color.g * factor),
		.b = (int)(color.b * factor)};
}

static t_color color_add(t_color c1, t_color c2)
{
	return (t_color){
		.t = c1.t,
		.r = fmin(c1.r + c2.r, 255),
		.g = fmin(c1.g + c2.g, 255),
		.b = fmin(c1.b + c2.b, 255)};
}

t_color phong_reflection(t_scene *scene, t_point P, t_vec4d N, t_vec4d V, t_object *obj)
{
	t_color final_color = {0, 0, 0, 0};
	size_t i;

	for (i = 0; i < scene->l; i++)
	{
		t_light light = scene->light[i];
		t_vec4d L = vec4d_normalize(vec4d_sub((t_vec4d){light.position.x, light.position.y, light.position.z, 1.0f},
											  (t_vec4d){P.x, P.y, P.z, 1.0f}));
		// Ambient Component
		t_color ambient = color_scale(scene->ambient.color, scene->ambient.intensity);

		// Diffuse Component
		float diff = fmax(0.0f, vec4d_dot(N, L));
		t_color diffuse = color_scale(light.color, diff * light.brightness);

		// Specular Component
		t_vec4d R = vec4d_reflect(L, N);
		float spec = powf(fmax(0.0f, vec4d_dot(R, V)), obj->shininess);
		t_color specular = color_scale(light.color, spec * light.brightness * obj->reflection);

		// Add contributions
		final_color = color_add(final_color, color_add(ambient, color_add(diffuse, specular)));
	}
	return final_color;
}
