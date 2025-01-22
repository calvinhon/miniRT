/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_ref.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 08:03:20 by marvin            #+#    #+#             */
/*   Updated: 2025/01/09 08:03:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
#define COMMON_H

#include "lag.h"	 // for t_vec4s, t_mat4s, and their funcs
#include <stdbool.h> // for `true`, `false`

typedef union u_vec4d
{
	float a[4];
	__m256d simd;
	uint64_t raw[4];
	struct
	{
		float x;
		float y;
		float z;
		float w;
	};
} __attribute((aligned(32))) t_vec4d;

typedef union u_vec4s
{
	float a[4];
	__m128 simd;
	uint32_t raw[4];
	struct
	{
		float x;
		float y;
		float z;
		float w;
	};
} __attribute((aligned(16))) t_vec4s;

typedef union u_vec3d
{
	float a[4];
	__m256d simd;
	struct
	{
		float x;
		float y;
		float z;
		float ignore;
	};
} __attribute((aligned(32))) t_vec3d;

typedef union u_vec2s
{
	float a[2];
	__m128d simd;
	struct
	{
		float x;
		float y;
	};
} __attribute((aligned(16))) t_vec2s;

// 2D Matrices can be held inside a single 128-bit vector, fix. (for all)
typedef union u_mat2d
{
	float a[2][2];
	__m128d simd[2];
	struct
	{
		t_vec2s r1;
		t_vec2s r2;
	};
} __attribute((aligned(16))) t_mat2d;

typedef union u_mat3d
{
	float a[4][4];
	__m256 simd[4];
	struct
	{
		t_vec3d r1;
		t_vec3d r2;
		t_vec3d r3;
		t_vec3d ignore;
	};
} __attribute((aligned(32))) t_mat3d;

typedef union u_mat4s
{
	float a[4][4];
	__m128 simd[4];
	__m256 _ymm[2];
	struct
	{
		t_vec4s r1;
		t_vec4s r2;
		t_vec4s r3;
		t_vec4s r4;
	};
} __attribute((aligned(16))) t_mat4s;

typedef union u_mat4d
{
	float a[4][4];
	__m256d simd[4];
	struct
	{
		t_vec4d r1;
		t_vec4d r2;
		t_vec4d r3;
		t_vec4d r4;
	};
} __attribute((aligned(32))) t_mat4d;

typedef union u_color
{
	t_vec4s v;
	struct
	{
		float a;
		float r;
		float g;
		float b;
	};
} t_color;

typedef struct s_canvas t_canvas;

typedef struct s_material
{
	t_color color;
	t_color xordc;
	float ambient;
	float diffuse;
	float specular;
	float sheen;
	float reflective;
	float transparency;
	float refractive_index;
	bool checkered;
	t_canvas *tex;
} t_material;

typedef struct s_material_colors
{
	int light_type;
	t_color intensity;
	t_color effective_color;
	t_color ambient;
	t_color diffuse;
	t_color specular;
	t_color return_color;
} t_material_colors;

typedef struct s_obj
{
	int type;
	t_vec4s center;
	t_mat4s inv_transform;
	t_mat4s transposed_inverse;
	t_mat4s rot;
	t_vec4s trans;
	t_vec4s scale;
	t_vec4s orientation;
	t_material material;
	float radius;
	union u_specs
	{
		struct
		{
			t_vec4s normal;
		};
		struct
		{
			float side_length;
		};
		struct
		{
			float min;
			float max;
			bool closed;
		};
	} specs;
} t_obj;

typedef struct s_intersection
{
	float t;
	t_obj *object;
	float n1;
	float n2;
} t_itx;

typedef struct s_intersection_group
{
	t_itx arr[200];
	int count;
} t_itx_grp;

typedef struct s_ray
{
	t_vec4s origin;
	t_vec4s dir;
} t_ray;

typedef struct s_camera
{
	bool is_set;
	int line_set;
	int hsize;
	int vsize;
	float fov;
	t_mat4s inv_transform;
	t_vec4s forward;
	t_vec4s up;
	t_vec4s left;
	t_mat4s rot;
	t_vec4s trans;
	t_vec4s scale;
	float half_width;
	float half_height;
	float half_view;
	float aspect_ratio;
	float pixel_size;
} t_camera;

typedef struct s_light
{
	int type;
	t_vec4s pos;
	float ratio;
	union u_light_type
	{
		struct s_point
		{
			t_color intensity;
		} point;
		struct s_spot
		{
			t_color intensity;
			t_vec4s orientation;
			float spot_angle;
		} spot;
	} specs;
} t_light;

typedef struct s_world
{
	bool refract_reflect;
	t_color ambiance;
	int num_shapes;
	int num_lights;
	t_obj *shapes;
	t_light *lights;
} t_world;

typedef struct s_canvas
{
	void *ptr;
	char *addr;
	int bpp;
	int bpp_8;
	int line_length;
	int endian;
	int tex_width;
	int tex_height;
} t_canvas;

typedef struct s_thread_data t_thread;

typedef struct s_tex_node
{
	char *name;
	t_canvas *tex;
} t_texture;

typedef struct s_program
{
	int runtime_error;
	int flt_operations;
	void *mlx;
	void *win;
	t_list *textures;
	t_canvas canvas;
	t_world world;
	t_camera cam;
	t_thread *pool;
	bool stop;
	float delta_time;
	struct s_select
	{
		bool is_cam;
		t_obj *object;
		t_vec4s ray_dir;
	} selected;
	struct s_ambient
	{
		bool is_set;
		int line_set;
		t_color color;
		float ratio;
	} ambiance;
	struct s_movement
	{
		bool w;
		bool a;
		bool s;
		bool d;
		bool up;
		bool down;
		bool left;
		bool right;
		bool space;
		bool lctrl;
		bool lshift;
	} movement;
	struct s_mouse
	{
		bool left_click;
	} mouse;
} t_program;

struct s_thread_data
{
	int id;
	pthread_t thread;
	t_program *context;
	int y;
	int y_f;
	int x;
	int x_f;
	bool work_ready;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};

typedef struct itx_computation
{
	bool shadowed;
	double t;
	t_obj *obj;
	t_vec4s p;
	t_vec4s over_point;
	t_vec4s under_point;
	t_vec4s eyev;
	t_vec4s normalv;
	t_vec4s reflect_v;
	int inside;
	double n1;
	double n2;
} t_comps;

/*--- PARSING ---*/

typedef struct s_validate_atof
{
	size_t sign_count;
	size_t dot_count;
	size_t digit_count;
	bool found_alpha;
} t_vatof;

#endif // !COMMON_H