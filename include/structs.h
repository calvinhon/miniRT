// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   structs.h                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/01/22 11:01:20 by chon              #+#    #+#             */
// /*   Updated: 2025/01/22 11:01:20 by chon             ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #ifndef STRUCTS_H
// #define STRUCTS_H

// #include <pthread.h>
// #include <immintrin.h> //__m256d, __m128)
// #include <stdint.h>	   // bit-wise & integer types
// #include <stdbool.h>   // boolean types
// #include <macros.h>
// #include <stdarg.h>

// typedef struct s_point
// {
// 	struct
// 	{
// 		float x;
// 		float y;
// 		float z;
// 		float p;
// 	};
// 	float arr[4];
// 	uint32_t pint[4];
// 	__m128 psimd;
// } __attribute((aligned(16))) t_point;

// typedef t_point t_point; // To silence faulty(?) VS Code warning:

// typedef struct s_vec4d
// {
// 	struct
// 	{
// 		float x;
// 		float y;
// 		float z;
// 		float p;
// 	};
// 	float arr[4];
// 	uint32_t vint[4];
// 	__m128 vsimd;
// } __attribute((aligned(16))) t_vec4d;

// typedef t_vec4d t_vec4d; // To silence faulty(?) VS Code warning:

// typedef struct s_color
// {
// 	struct
// 	{
// 		float r;
// 		float g;
// 		float b;
// 		float t;
// 	};
// 	t_vec4d v;
// } t_color;

// typedef struct s_vec2d
// {
// 	float x;
// 	float y;
// } t_vec2d;

// typedef struct s_vec3d
// {
// 	float x;
// 	float y;
// 	float z;
// } t_vec3d;

// typedef struct s_shear
// {
// 	float x_y;
// 	float x_z;
// 	float y_x;
// 	float y_z;
// 	float z_x;
// 	float z_y;
// } t_shear;

// typedef struct s_mat2d
// {
// 	float matrix[4];
// } t_mat2d;

// typedef struct s_mat3d
// {
// 	float matrix[9];
// } t_mat3d;

// typedef struct s_mat4d
// {
// 	float matrix[16];
// } t_mat4d;

// typedef struct s_ray
// {
// 	t_point origin;
// 	t_vec4d direction;
// } t_ray;

// // Light source
// typedef struct s_light
// {
// 	t_point position;
// 	float brightness;
// 	t_color color;
// } t_light;

// // Camera
// typedef struct s_camera
// {
// 	bool ini;
// 	t_point origin;
// 	t_vec4d direction;
// 	float fov;
// 	float hsize;
// 	float vsize;
// 	t_mat4d transform;
// 	t_mat4d inv_transform;
// 	t_vec4d forward;
// 	t_vec4d up;
// 	t_vec4d left;
// 	t_mat4d rot;
// 	t_vec4d trans;
// 	t_vec4d scale;
// 	float half_width;
// 	float half_height;
// 	float half_view;
// 	float aspect_ratio;
// 	float pixel_size;
// } t_camera;

// // Object types
// enum e_object_type
// {
// 	SPHERE,
// 	PLANE,
// 	CYLINDER,
// 	CUBE,
// 	CONE
// };

// // Pattern types

// // Ambient
// typedef struct s_ambient
// {
// 	float intensity;
// 	t_color color;
// } t_ambient;

// // Data for objects

// typedef struct s_material
// {
// 	t_color color;
// 	float ambient_s;
// 	float diffuse_s;
// 	float specular_s;
// 	float shininess;
// 	t_pattern *pattern;
// 	float reflective;
// } t_material;

// typedef struct s_material_colors
// {
// 	int light_type;
// 	t_color intensity;
// 	t_color effective_color;
// 	t_color ambient;
// 	t_color diffuse;
// 	t_color specular;
// 	t_color return_color;
// } t_material_colors;

// // typedef struct s_material
// // {
// // 	t_color		color;
// // 	t_color		xordc;
// // 	float		ambient;
// // 	float		diffuse;
// // 	float		specular;
// // 	float		shininess;
// // 	float		reflective;
// // 	float		transparency;
// // 	float		refractive_index;
// // 	bool		checkered;
// // 	t_frame	*graphic;
// // }	t_material;

// // Generic object structure
// typedef struct s_object
// {
// 	int type;
// 	t_point center;
// 	void *data;
// 	t_mat4d rotate;
// 	t_mat4d scale;
// 	t_mat4d translate;
// 	t_mat4d transform;
// 	t_mat4d inv_transform;
// 	t_material material;
// 	union u_specs
// 	{
// 		struct t_cyl
// 		{
// 			float min_y;
// 			float max_y;
// 			bool closed;
// 		} t_cyl;
// 		struct
// 		{
// 			t_vec4d normal;
// 		};
// 		struct s_cube
// 		{
// 			float side_length;
// 		} t_cube;
// 	} specs;
// } t_object;

// typedef struct s_itx
// {
// 	float t;
// 	t_object *obj;
// 	float n1;
// 	float n2;
// } t_itx;

// typedef struct s_itx_set
// {
// 	t_itx arr[MAX_ITX];
// 	int count;
// } t_itx_grp;

// typedef struct s_comps_for_xs
// {
// 	float t;
// 	t_object *obj;
// 	t_point p;
// 	t_point over_point;
// 	t_vec4d under_point;
// 	t_vec4d eye_v;
// 	t_vec4d normal_v;
// 	t_vec4d reflect_v;
// 	float n1;
// 	float n2;
// 	t_color ambient;
// 	t_color diffuse;
// 	t_color specular;
// } t_comps;

// typedef struct s_scene
// {
// 	bool refract_reflect;
// 	t_ambient ambient;
// 	int num_shapes;
// 	int num_lights;
// 	t_camera camera;
// 	size_t l;
// 	size_t idx_l;
// 	t_light *lights;
// 	t_object *objs;
// 	size_t n_objs;
// 	size_t idx_obj;
// 	size_t a;
// 	size_t c;
// 	size_t pl;
// 	size_t sp;
// 	size_t cy;
// 	size_t cu;
// 	size_t co;
// } t_scene;

// typedef struct s_frame
// {
// 	void *mlx;
// 	void *win;
// 	void *img;
// 	char *addr;
// 	int bpp;
// 	int bpp_8;
// 	int l_len;
// 	int end;
// } t_frame;

// typedef struct s_minirt t_minirt;

// typedef struct s_unit
// {
// 	int id;
// 	pthread_t thread;
// 	t_minirt *minirt;
// 	int y;
// 	int y_f;
// 	int x;
// 	int x_f;
// 	bool ready;
// 	pthread_mutex_t mutex;
// 	pthread_cond_t cond;
// } t_unit;

// typedef struct s_texture
// {
// 	char *name;
// 	t_frame *tex;
// } t_texture;

// typedef struct s_minirt
// {
// 	// t_frame	graphic;
// 	void *mlx;
// 	void *win;
// 	t_frame env;
// 	t_camera cam;
// 	t_scene scene;
// 	t_unit *units;
// 	// t_list		*textures;
// 	int error;
// 	bool stop;
// 	float time;

// 	// moving object
// 	bool is_cam;
// 	t_object *obj;
// 	t_vec4d ray_dir;

// 	struct s_move
// 	{
// 		bool w;
// 		bool a;
// 		bool s;
// 		bool d;
// 		bool up;
// 		bool down;
// 		bool left;
// 		bool right;
// 		bool space;
// 		bool lctrl;
// 		bool lshift;
// 	} move;

// 	struct s_mouse
// 	{
// 		bool left_click;
// 	} mouse;

// } t_minirt;

// #endif