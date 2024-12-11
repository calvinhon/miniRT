#include "mlx_macos/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MOVE_SPEED 10.0f
#define ROTATE_SPEED 5.0f

#define KEY_W 13  // Move forward
#define KEY_S 1   // Move backward
#define KEY_A 0   // Move left
#define KEY_D 2   // Move right
#define KEY_ESC 53 // Escape key to exit

// Vector 3 Dimension
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

// Light source
typedef struct s_light
{
    t_vec3d position;
    float brightness;
    t_vec3d color;
} t_light;

// Scene objects
typedef struct s_plane
{
    t_vec3d point;   // A point on the plane
    t_vec3d normal;  // Normal vector to the plane
    t_vec3d color;   // Color of the plane
} t_plane;

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

typedef struct s_cone
{
    t_vec3d apex;     // Apex of the cone
    t_vec3d axis;     // Axis vector (direction of the cone)
    float angle;      // Half-angle of the cone in radians
    t_vec3d color;    // Color of the cone
} t_cone;

typedef struct s_cube
{
    t_vec3d min;      // Minimum corner of the cube
    t_vec3d max;      // Maximum corner of the cube
    t_vec3d color;    // Color of the cube
} t_cube;

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
    t_cone  cone;        // Add cone
    t_cube cube;         // Add cube
    float ambient;        // Ambient light intensity
    t_vec3d ambient_light_color;

    void *mlx_ptr;
    void *win_ptr;
} t_scene;

// Thread data structure
typedef struct s_thread_data
{
    int thread_id;
    int thread_count;
    int width;
    int height;
    t_scene *scene;
    void *mlx_ptr;
    void *win_ptr;
} t_thread_data;

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

// Key press handler to move the camera position
int handle_key_press(int keycode, t_scene *scene)
{
    if (keycode == 123)  // Left arrow
        scene->camera.origin.x -= MOVE_SPEED;  // Move camera left
    else if (keycode == 124)  // Right arrow
        scene->camera.origin.x += MOVE_SPEED;  // Move camera right
    else if (keycode == 126)  // Up arrow
        scene->camera.origin.y += MOVE_SPEED;  // Move camera up
    else if (keycode == 125)  // Down arrow
        scene->camera.origin.y -= MOVE_SPEED;  // Move camera down
    else if (keycode == 13)  // W key
        scene->camera.origin.z += MOVE_SPEED;  // Move camera forward (along negative Z-axis)
    else if (keycode == 1)  // S key
        scene->camera.origin.z -= MOVE_SPEED;  // Move camera backward (along negative Z-axis)
    else if (keycode == 12)  // Q key
        scene->camera.origin.y += MOVE_SPEED;  // Move camera up (Y-axis)
    else if (keycode == 14)  // E key
        scene->camera.origin.y -= MOVE_SPEED;  // Move camera down (Y-axis)
    else if (keycode == 53)  // ESC key
        exit(0);  // Exit the program
    
    return (0);
}

// All intersection with objects
int intersect_ray_plane(t_ray ray, t_plane plane, float *t)
{
    float denom = vdot_vec3d(ray.direction, plane.normal);
    if (fabs(denom) > 1e-6) // Check if ray is not parallel to the plane
    {
        t_vec3d p0l0 = sub_vec3d(plane.point, ray.origin);
        *t = vdot_vec3d(p0l0, plane.normal) / denom;
        return (*t >= 0);
    }
    return (0);
}

int intersect_ray_sphere(t_ray ray, t_sphere sphere, float *t)
{
    t_vec3d oc = sub_vec3d(ray.origin, sphere.center);
    float a = vdot_vec3d(ray.direction, ray.direction);
    float b = 2.0f * vdot_vec3d(oc, ray.direction);
    float c = vdot_vec3d(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0)
    {
        *t = (-b - sqrtf(discriminant)) / (2.0f * a);
        if (*t < 0) // check if the intersection is in front of the ray origin
            *t = (-b + sqrtf(discriminant)) / (2.0f * a);
        return (*t >= 0);
    }
    return (0);
}

int intersect_ray_cylinder(t_ray ray, t_cylinder cylinder, float *t)
{
    t_vec3d oc = sub_vec3d(ray.origin, cylinder.base);
    t_vec3d axis_normal = normalize_vec3d(cylinder.axis);
    float a = vdot_vec3d(ray.direction, ray.direction) - powf(vdot_vec3d(ray.direction, axis_normal), 2);
    float b = 2.0f * (vdot_vec3d(oc, ray.direction) - vdot_vec3d(oc, axis_normal) * vdot_vec3d(ray.direction, axis_normal));
    float c = vdot_vec3d(oc, oc) - powf(vdot_vec3d(oc, axis_normal), 2) - cylinder.radius * cylinder.radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant >= 0)
    {
        *t = (-b - sqrtf(discriminant)) / (2.0f * a);
        if (*t < 0) // check if the intersection is in front of the ray origin
            *t = (-b + sqrtf(discriminant)) / (2.0f * a);
        return (*t >= 0);
    }
    return (0);
}

int intersect_ray_cone(t_ray ray, t_cone cone, float *t)
{
    t_vec3d oc = sub_vec3d(ray.origin, cone.apex);
    t_vec3d axis_normal = normalize_vec3d(cone.axis);
    float tan_angle = tanf(cone.angle);
    float cos_angle = cosf(cone.angle);
    float k = powf(tan_angle, 2);
    float a = vdot_vec3d(ray.direction, ray.direction) - (1 + k) * powf(vdot_vec3d(ray.direction, axis_normal), 2);
    float b = 2.0f * (vdot_vec3d(oc, ray.direction) - (1 + k) * vdot_vec3d(oc, axis_normal) * vdot_vec3d(ray.direction, axis_normal));
    float c = vdot_vec3d(oc, oc) - (1 + k) * powf(vdot_vec3d(oc, axis_normal), 2);

    float discriminant = b * b - 4 * a * c;
    if (discriminant >= 0)
    {
        *t = (-b - sqrtf(discriminant)) / (2.0f * a);
        if (*t < 0) // check if the intersection is in front of the ray origin
            *t = (-b + sqrtf(discriminant)) / (2.0f * a);
        return (*t >= 0);
    }
    return (0);
}

int intersect_ray_cube(t_ray ray, t_cube cube, float *t)
{
    t_vec3d inv_dir = (t_vec3d){1.0f / ray.direction.x, 1.0f / ray.direction.y, 1.0f / ray.direction.z};
    t_vec3d min_t = scale_vec3d(sub_vec3d(cube.min, ray.origin), inv_dir);
    t_vec3d max_t = scale_vec3d(sub_vec3d(cube.max, ray.origin), inv_dir);

    float t1 = fmaxf(fminf(min_t.x, max_t.x), fmaxf(fminf(min_t.y, max_t.y), fmaxf(fminf(min_t.z, max_t.z), 0.0f)));
    float t2 = fminf(fmaxf(min_t.x, max_t.x), fminf(fmaxf(min_t.y, max_t.y), fminf(max_t.z, min_t.z)));

    if (t2 >= t1)
    {
        *t = t1;
        return (1);
    }
    return (0);
}

// Calculate color contribution from diffuse and ambient lighting
t_vec3d calculate_lighting(t_vec3d hit_point, t_vec3d normal, t_scene *scene)
{
    t_vec3d light_dir = normalize_vec3d(sub_vec3d(scene->light.position, hit_point));
    float diff = fmaxf(vdot_vec3d(normal, light_dir), 0.0f);

    // Ambient light calculation
    t_vec3d ambient = scale_vec3d(scene->ambient_light_color, scene->ambient);

    // Diffuse light calculation
    t_vec3d diffuse = scale_vec3d(scene->light.color, diff * scene->light.brightness);

    return add_vec3d(ambient, diffuse);
}

// Raytracing function executed by each thread
void *render_slice(void *arg)
{
    t_thread_data *data = (t_thread_data *)arg;
    int start_row = data->thread_id * (data->height / data->thread_count);
    int end_row = (data->thread_id + 1) * (data->height / data->thread_count);

    for (int y = start_row; y < end_row; y++)
    {
        for (int x = 0; x < data->width; x++)
        {
            float t;
            t_ray ray = {data->scene->camera.origin, normalize_vec3d(add_vec3d(scale_vec3d(data->scene->camera.direction, x - data->width / 2), scale_vec3d(data->scene->camera.origin, -1.0f)))};
            t_vec3d color = {0, 0, 0};

            // Check intersection with all objects in the scene
            if (intersect_ray_plane(ray, data->scene->plane, &t))
                color = calculate_lighting(add_vec3d(ray.origin, scale_vec3d(ray.direction, t)), data->scene->plane.normal, data->scene);
            if (intersect_ray_sphere(ray, data->scene->sphere, &t))
                color = calculate_lighting(add_vec3d(ray.origin, scale_vec3d(ray.direction, t)), normalize_vec3d(sub_vec3d(ray.origin, data->scene->sphere.center)), data->scene);
            if (intersect_ray_cylinder(ray, data->scene->cylinder, &t))
                color = calculate_lighting(add_vec3d(ray.origin, scale_vec3d(ray.direction, t)), normalize_vec3d(sub_vec3d(ray.origin, data->scene->cylinder.base)), data->scene);
            if (intersect_ray_cone(ray, data->scene->cone, &t))
                color = calculate_lighting(add_vec3d(ray.origin, scale_vec3d(ray.direction, t)), normalize_vec3d(sub_vec3d(ray.origin, data->scene->cone.apex)), data->scene);
            if (intersect_ray_cube(ray, data->scene->cube, &t))
                color = calculate_lighting(add_vec3d(ray.origin, scale_vec3d(ray.direction, t)), normalize_vec3d(sub_vec3d(ray.origin, data->scene->cube.min)), data->scene);

            // Set pixel color in the window
            mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, (int)(color.x * 255) << 16 | (int)(color.y * 255) << 8 | (int)(color.z * 255));
        }
    }

    return NULL;
}

int main()
{
   
    // Initialize the window using MLX
    void *mlx_ptr = mlx_init();
    void *win_ptr = mlx_new_window(mlx_ptr, 800, 600, "Multi-threaded Raytracer");
   
    t_scene scene = {
        .camera = {{0, 3, 10}, {0, 0, -1}, 90},  // Camera moved to Z=10 for a better view of the objects
        .light = {{5, 5, 5}, 0.8f, {255, 255, 255}},  // Light positioned above and to the right of the camera
        .sphere = {{0, 0, -5}, 1.0f, {255, 0, 0}},  // Red sphere at Z=-5
        .cylinder = {{-4, 0, -10}, {0, 1, 0}, 1.0f, 3.0f, {0, 0, 255}},  // Blue cylinder at X=-4, Z=-10
        .plane = {{0, -2, 0}, {0, 1, 0}, {0, 255, 0}},  // Green ground plane at Z=0, Y=-2
        .cone = {{5, 0, -10}, {0, 1, -0.2}, M_PI / 4, {255, 255, 0}},  // Yellow cone at X=5, Z=-10
        .cube = {{-6, -1, -15}, {2, 2, -12}, {0, 255, 255}},  // Cyan cube at X=-6, Z=-15
        .ambient = 0.25f,  // Ambient light intensity
        .ambient_light_color = {255, 255, 255}, // White ambient light
        .mlx_ptr = mlx_ptr,
        .win_ptr = win_ptr
    };
    

    // Create threads
    pthread_t threads[4];
    t_thread_data thread_data[4];
    for (int i = 0; i < 4; i++)
    {
        thread_data[i].thread_id = i;
        thread_data[i].thread_count = 4;
        thread_data[i].width = 800;
        thread_data[i].height = 600;
        thread_data[i].scene = &scene;
        thread_data[i].mlx_ptr = scene.mlx_ptr;
        thread_data[i].win_ptr = scene.win_ptr;
        pthread_create(&threads[i], NULL, render_slice, &thread_data[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }

    mlx_loop(scene.mlx_ptr);

    return 0;
}
