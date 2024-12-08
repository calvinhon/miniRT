/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_multi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:55:10 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/08 16:14:11 by honguyen         ###   ########.fr       */
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
    t_vec3d point;   // A point on the plane
    t_vec3d normal;  // Normal vector to the plane
    t_vec3d color;   // Color of the plane
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

typedef struct s_cylinder
{
    t_vec3d base;     // base center of the cylinder
    t_vec3d axis;     // axis vector (direction of the cylinder)
    float radius;     // radius of the cylinder
    float height;     // height of the cylinder
    t_vec3d color;    // color of the cylinder
} t_cylinder;

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
    t_cylinder cylinder; // Add cylinder
    float ambient;        // Ambient light intensity
    t_vec3d ambient_light_color;
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
        a.x * b.y - a.y * b.x
    };
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
    if (fabs(denom) > 1e-6) // Check if ray is not parallel to the plane
    {
        t_vec3d p0l0 = sub_vec3d(plane.point, ray.origin);
        *t = vdot_vec3d(p0l0, plane.normal) / denom;
        return (*t >= 0); // Intersection occurs if t is non-negative
    }
    return 0; // No intersection
}

t_vec3d calculate_normal_plane(t_vec3d hit_point, t_plane plane)
{
    return normalize_vec3d(plane.normal);
}



int intersect_ray_sphere(t_ray ray, t_sphere sphere, float *t)
{
    t_vec3d oc = sub_vec3d(ray.origin, sphere.center);
    float a = vdot_vec3d(ray.direction, ray.direction);
    float b = 2.0f * vdot_vec3d(oc, ray.direction);
    float c = vdot_vec3d(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = b * b - 4.0f * a * c;

    if (discriminant > 0) {
        *t = (-b - sqrtf(discriminant)) / (2.0f * a);
        if (*t > 0) return 1; // Intersection
    }
    return 0;
}


int intersect_ray_cylinder(t_ray ray, t_cylinder cylinder, float *t)
{
    t_vec3d d = ray.direction;
    t_vec3d oc = sub_vec3d(ray.origin, cylinder.base);
    t_vec3d a = cylinder.axis;

    float a_coeff = vdot_vec3d(d, d) - powf(vdot_vec3d(d, a), 2);
    float b_coeff = 2 * (vdot_vec3d(d, oc) - vdot_vec3d(d, a) * vdot_vec3d(oc, a));
    float c_coeff = vdot_vec3d(oc, oc) - powf(vdot_vec3d(oc, a), 2) - cylinder.radius * cylinder.radius;

    float discriminant = b_coeff * b_coeff - 4 * a_coeff * c_coeff;
    if (discriminant < 0)
        return 0;

    float sqrt_disc = sqrtf(discriminant);
    float t1 = (-b_coeff - sqrt_disc) / (2 * a_coeff);
    float t2 = (-b_coeff + sqrt_disc) / (2 * a_coeff);

    *t = (t1 > t2 && t2 > 0) ? t2 : t1;
    if (*t < 0)
        return 0;

    t_vec3d hit_point = add_vec3d(ray.origin, scale_vec3d(ray.direction, *t));
    t_vec3d hit_vec = sub_vec3d(hit_point, cylinder.base);
    float height = vdot_vec3d(hit_vec, a);
    if (height < 0 || height > cylinder.height)
        return 0;

    return 1;
}



t_vec3d calculate_normal_cylinder(t_vec3d hit_point, t_cylinder cylinder)
{
    t_vec3d hit_vec = sub_vec3d(hit_point, cylinder.base);
    float height = vdot_vec3d(hit_vec, cylinder.axis);
    t_vec3d proj = scale_vec3d(cylinder.axis, height);
    return normalize_vec3d(sub_vec3d(hit_vec, proj));
}



// Ambient light calculation: applying intensity and light color
t_vec3d apply_ambient_light(t_vec3d base_color, t_vec3d light_color, float ambient_intensity)
{
    // Apply ambient intensity (scaling effect) and light color (RGB scaling)
    t_vec3d ambient_light = {
        base_color.x * ambient_intensity * (light_color.x / 255.0f),
        base_color.y * ambient_intensity * (light_color.y / 255.0f),
        base_color.z * ambient_intensity * (light_color.z / 255.0f)
    };
    return ambient_light;
}

// Updated calculate_color function
t_vec3d calculate_color(t_ray ray, t_scene scene)
{
    float t;
    t_vec3d color = {0, 0, 0};
    if (intersect_ray_sphere(ray, scene.sphere, &t))
    {
        t_vec3d hit_point = add_vec3d(ray.origin, scale_vec3d(ray.direction, t));
        t_vec3d normal = normalize_vec3d(sub_vec3d(hit_point, scene.sphere.center));
        t_vec3d light_dir = normalize_vec3d(sub_vec3d(scene.light.position, hit_point));

        float diffuse = fmaxf(0.0f, vdot_vec3d(normal, light_dir));
        t_vec3d ambient_light = apply_ambient_light(scene.sphere.color, scene.ambient_light_color, scene.ambient);

        color = add_vec3d(color, ambient_light);
        color = add_vec3d(color, scale_vec3d(scene.sphere.color, diffuse * scene.light.brightness));
    }
    else if (intersect_ray_cylinder(ray, scene.cylinder, &t))
    {
        t_vec3d hit_point = add_vec3d(ray.origin, scale_vec3d(ray.direction, t));
        t_vec3d normal = calculate_normal_cylinder(hit_point, scene.cylinder);
        t_vec3d light_dir = normalize_vec3d(sub_vec3d(scene.light.position, hit_point));

        float diffuse = fmaxf(0.0f, vdot_vec3d(normal, light_dir));
        t_vec3d ambient_light = apply_ambient_light(scene.cylinder.color, scene.ambient_light_color, scene.ambient);

        color = add_vec3d(color, ambient_light);
        color = add_vec3d(color, scale_vec3d(scene.cylinder.color, diffuse * scene.light.brightness));
    }
    // Check if ray intersects with the plane
    else if (intersect_ray_plane(ray, scene.plane, &t))
    {
        t_vec3d hit_point = add_vec3d(ray.origin, scale_vec3d(ray.direction, t));
        t_vec3d normal = calculate_normal_plane(hit_point, scene.plane);
        t_vec3d light_dir = normalize_vec3d(sub_vec3d(scene.light.position, hit_point));

        // Calculate diffuse lighting
        float diffuse = fmaxf(0.0f, vdot_vec3d(normal, light_dir));

        // Apply ambient light with the intensity and light color
        t_vec3d ambient_light = apply_ambient_light(scene.plane.color, scene.ambient_light_color, scene.ambient);

        // Final color: Ambient + Diffuse Lighting
        color = add_vec3d(color, ambient_light);
        color = add_vec3d(color, scale_vec3d(scene.plane.color, diffuse * scene.light.brightness));
    }

    return color;
}
void render_scene(t_scene scene, void *mlx_ptr, void *win_ptr)
{
    int width = 800, height = 600;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
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
    if (!mlx_ptr) {
        printf("Error initializing mlx\n");
        return 1;
    }

    // Create a new window
    win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Raytracing Window");
    if (!win_ptr) {
        printf("Error creating window\n");
        return 1;
    }

    // Define scene with ambient light factor separately in the scene structure
    t_scene scene = {
        .camera = {{0, 0, 0}, {0, 0, -1}, 120},  // Camera at the origin, looking down the negative Z-axis
        .light = {{25, 0, -10}, 0.8f, {255, 255, 255}},  // White light, positioned somewhere in the scene
        .sphere = {{0, 0, -10}, 1.5f, {255, 0, 0}},  // Red sphere
        .cylinder = {{-5, -5, -20}, {0, 1, 0}, 1.0f, 5.0f, {0, 0, 255}}, // Red cylinder at z = -10, aligned along the y-axis
        .plane = {{0, 0, -20}, {0, 1, 1}, {0, 255, 0}},  // Blue plane at z = -10, normal pointing up
        .ambient = 0.25f,  // Ambient light intensity (20%)
        .ambient_light_color = {255, 255, 255}  // White ambient light color
    };



    // Render the scene to the window
    render_scene(scene, mlx_ptr, win_ptr);

    // Wait for user to close the window
    mlx_loop(mlx_ptr);

    return 0;
}

// gcc -o raytracer raytracer.c -L./mlx_macos  -lmlx -framework OpenGL -framework AppKit
// ./raytracer
