/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:55:10 by honguyen          #+#    #+#             */
/*   Updated: 2025/01/16 16:09:54 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_macos/mlx.h"
#include <math.h>
#include <stdio.h>

typedef struct s_vec3d
{
	float x;
	float y;
	float z;
} t_vec3d;

typedef struct s_ray
{
	t_vec3d origin;
	t_vec3d direction;
} t_ray;

typedef struct s_plane
{
	t_vec3d point;
	t_vec3d normal;
} t_plane;

typedef struct s_light
{
	t_vec3d position;
	float brightness;
	t_vec3d color;
} t_light;

typedef struct s_sphere
{
	t_vec3d center;
	float radius;
	t_vec3d color;
} t_sphere;

typedef struct s_camera
{
	t_vec3d origin;
	t_vec3d direction;
	float fov;
} t_camera;

typedef struct s_scene
{
	t_camera camera;
	t_light light;
	t_plane plane;
	t_sphere sphere;
	float ambient; // Ambient light intensity
} t_scene;

// Vector operations
t_vec3d add_vec3d(t_vec3d a, t_vec3d b)
{
	return (t_vec3d){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vec3d sub_vec3d(t_vec3d a, t_vec3d b)
{
	return (t_vec3d){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vec3d scale_vec3d(t_vec3d v, float k)
{
	return (t_vec3d){v.x * k, v.y * k, v.z * k};
}

float vdot_vec3d(t_vec3d a, t_vec3d b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec3d cross_vec3d(t_vec3d a, t_vec3d b)
{
	return (t_vec3d){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x};
}

float length_vec3d(t_vec3d v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3d normalize_vec3d(t_vec3d v)
{
	float len = length_vec3d(v);
	return scale_vec3d(v, 1.0f / len);
}

int intersect_ray_plane(t_ray ray, t_plane plane, float *t)
{
	float denom = vdot_vec3d(ray.direction, plane.normal);
	if (denom == 0)
		return 0; // No intersection, ray is parallel to the plane

	t_vec3d p0l0 = sub_vec3d(plane.point, ray.origin);
	*t = vdot_vec3d(p0l0, plane.normal) / denom;
	return *t >= 0;
}

int intersect_ray_sphere(t_ray ray, t_sphere sphere, float *t)
{
	t_vec3d oc = sub_vec3d(ray.origin, sphere.center);
	float a = vdot_vec3d(ray.direction, ray.direction);
	float b = 2.0f * vdot_vec3d(oc, ray.direction);
	float c = vdot_vec3d(oc, oc) - sphere.radius * sphere.radius;
	float discriminant = b * b - 4.0f * a * c;

	if (discriminant > 0)
	{
		*t = (-b - sqrtf(discriminant)) / (2.0f * a);
		if (*t > 0)
			return 1; // Intersection
	}
	return 0;
}

t_vec3d calculate_color(t_ray ray, t_scene scene)
{
	float t;
	t_vec3d color = {0, 0, 0}; // Default background color
	// Check if ray intersects with the sphere
	if (intersect_ray_sphere(ray, scene.sphere, &t))
	{
		t_vec3d hit_point = add_vec3d(ray.origin, scale_vec3d(ray.direction, t));
		t_vec3d normal = normalize_vec3d(sub_vec3d(hit_point, scene.sphere.center));
		t_vec3d light_dir = normalize_vec3d(sub_vec3d(scene.light.position, hit_point));

		// Calculate diffuse lighting
		float diffuse = fmaxf(0.0f, vdot_vec3d(normal, light_dir));

		// Ambient light effect: Added to the color from scene.ambient
		t_vec3d ambient_light = scale_vec3d(scene.sphere.color, scene.ambient);

		// Final color: Ambient + Diffuse Lighting
		color = add_vec3d(color, ambient_light);													 // Add ambient light
		color = add_vec3d(color, scale_vec3d(scene.sphere.color, diffuse * scene.light.brightness)); // Add diffuse lighting
	}
	return color;
}

void render_scene(t_scene scene, void *mlx_ptr, void *win_ptr)
{
	int width = 800, height = 600;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			float px = (2 * (x + 0.5f) / (float)width - 1) * tanf(scene.camera.fov / 2);
			float py = (1 - 2 * (y + 0.5f) / (float)height) * tanf(scene.camera.fov / 2);
			px *= (float)width / (float)height;
			t_vec3d ray_dir = {px, py, -1};
			ray_dir = normalize_vec3d(ray_dir);
			t_ray ray = {scene.camera.origin, ray_dir};
			t_vec3d color = calculate_color(ray, scene);
			int r = (int)(color.x);
			int g = (int)(color.y);
			int b = (int)(color.z);

			// Put the pixel to the window using mlx_pixel_put
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, (r << 16) | (g << 8) | b);
		}
	}
}

int main()
{
	void *mlx_ptr;
	void *win_ptr;

	// Initialize mlx
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
	{
		printf("Error initializing mlx\n");
		return 1;
	}

	// Create a new window
	win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Raytracing Window");
	if (!win_ptr)
	{
		printf("Error creating window\n");
		return 1;
	}

	// Define scene with ambient light factor separately in the scene structure
	t_scene scene = {
		.camera = {{0, 0, 0}, {0, 0, -1}, 120},
		.light = {{25, 20, -30}, 0.9f, {255, 0, 0}},
		.sphere = {{0, 0, -10}, 1.0f, {0, 254, 0}},
		.plane = {{0, -20, 0}, {0, 1, 0}},
		.ambient = 0.2f // Ambient light intensity
	};

	// Render the scene to the window
	render_scene(scene, mlx_ptr, win_ptr);

	// Wait for user to close the window
	mlx_loop(mlx_ptr);

	return 0;
}

// gcc -o raytracer raytracer.c -L./mlx_macos  -lmlx -framework OpenGL -framework AppKit
// ./raytracer
