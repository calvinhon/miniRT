#include "../include/lighting_and_shading.h"
#include <stdio.h>

float intersect_ray_with_sphere(t_point origin, t_vec4d direction, t_sphere sphere)
{
	// Transform the ray to the sphere's local space
	t_point ray_origin = mult_mat4d_pt4d(inverse_mat4d(sphere.transform), origin);
	t_vec4d ray_direction = mult_mat4d_vec4d(inverse_mat4d(sphere.transform), direction);

	// Sphere is centered at origin in local space
	t_vec4d sphere_to_ray = subtract_points(ray_origin, create_point(0, 0, 0));

	// Quadratic equation coefficients
	float a = dot(ray_direction, ray_direction);
	float b = 2 * dot(ray_direction, sphere_to_ray);
	float c = dot(sphere_to_ray, sphere_to_ray) - 1; // Radius is 1 in local space

	// Solve the quadratic equation: at^2 + bt + c = 0
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		// No intersection
		return -1;
	}

	// Compute the two solutions
	float t1 = (-b - sqrt(discriminant)) / (2 * a);
	float t2 = (-b + sqrt(discriminant)) / (2 * a);

	// Return the closest positive intersection (if any)
	if (t1 > 0 && t2 > 0)
		return fmin(t1, t2);
	else if (t1 > 0)
		return t1;
	else if (t2 > 0)
		return t2;

	// No positive intersection
	return -1;
}

// Placeholder function for drawing pixels
void draw_pixel(int x, int y, t_color color)
{
	// This should integrate with your graphics library
	printf("Drawing pixel at (%d, %d): Color(%f, %f, %f)\n", x, y, color.r, color.g, color.b);
}

void render_sphere_with_phong_model(int width, int height)
{
	t_sphere sphere;
	t_light light;
	t_material material;
	t_point light_position;
	t_color light_color;

	// Set up the sphere
	sphere.transform = identity_mat4d();
	sphere.material.color = create_color(1, 0.2, 0.2); // Red color
	sphere.material.ambient = create_color(0.1, 0.1, 0.1);
	sphere.material.diffuse = 0.7;
	sphere.material.specular = create_color(1, 1, 1);
	sphere.material.shininess = 100;

	// Set up the light source
	light_position = create_point(-10, 10, -10);
	light_color = create_color(1, 1, 1); // White light
	light.position = light_position;
	light.color = light_color;

	// Set up the camera and viewport
	t_point camera_position = create_point(0, 0, -5);
	t_vec4d eye_vector;

	float aspect_ratio = (float)width / height;
	float pixel_size = 2.0 / height; // Assume field of view fits within [-1, 1]
	float half_width = aspect_ratio;
	float half_height = 1.0;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			float world_x = -half_width + (x + 0.5) * pixel_size;
			float world_y = half_height - (y + 0.5) * pixel_size;

			t_point world_point = create_point(world_x, world_y, 0);
			t_vec4d ray_direction = normalize(subtract_points(world_point, camera_position));
			eye_vector = negate_vector(ray_direction);

			// Assume the sphere's center is at the origin
			float t = intersect_ray_with_sphere(camera_position, ray_direction, sphere);

			if (t > 0) // If there's an intersection
			{
				t_point intersection_point = add_points(camera_position, scale_vector(ray_direction, t));
				t_vec4d normal_vector = sphere_normal_at(sphere, intersection_point);

				t_color pixel_color = lighting(sphere, light, intersection_point, eye_vector);
				draw_pixel(x, y, pixel_color); // Placeholder function to draw pixel to canvas
			}
			else
			{
				draw_pixel(x, y, create_color(0, 0, 0)); // Background is black
			}
		}
	}
}

int main()
{
	int width = 800;
	int height = 600;

	render_sphere_with_phong_model(width, height);

	return 0;
}
