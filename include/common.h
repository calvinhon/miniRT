/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:38:28 by nth          #+#    #+#             */
/*   Updated: 2024/10/09 05:00:45 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include "minirt_math.h"

enum e_object_types
{
	SPHERE,
	CYLINDER,
	PLANE,
	CUBE,
	CONE,
	SPOT_LIGHT,
	POINT_LIGHT
};

typedef struct s_color
{
	float a;
	float r;
	float g;
	float b;
} t_color;

typedef struct s_frame t_frame;

enum e_pattern_type
{
	STRIPED,
	GRADIENT,
	RING,
	CHECKER
};

typedef struct s_pattern
{
	int type;
	t_color a;
	t_color b;
	t_mat4d transform;
	t_mat4d inv_transform;
	float p_scale;
} t_pattern;

typedef struct s_perturbed
{
	int i;
	int j;
	int k;
	float u;
	float v;
	float w;
	int a;
	int aa;
	int ab;
	int b;
	int ba;
	int bb;
	float g1;
	float g2;
	float g3;
	float g4;
	float g5;
	float g6;
	float g7;
	float g8;
} t_perturbed;

typedef struct s_material
{
	t_color color;
	t_color xordc;
	float ambient_s;
	float diffuse_s;
	float specular_s;
	float shininess;
	float reflective;
	float transparency;
	float refractive_index;
	bool checkered;
	t_pattern *pattern;
	t_frame *fra_tex;
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

typedef struct s_object
{
	int type;
	t_point center;
	t_mat4d inv_transform;
	t_mat4d transposed_inverse;
	t_mat4d rot;
	t_mat4d translate;
	t_mat4d scale;
	t_vec4d orientation;
	t_material material;
	float radius;
	union u_specs
	{
		struct
		{
			t_vec4d normal;
		};
		struct
		{
			float side_length;
		};
		struct
		{
			float min_y;
			float max_y;
			bool closed;
		};
	} specs;
} t_object;

typedef struct s_itx
{
	float t;
	t_object *obj;
	float n1;
	float n2;
} t_itx;

typedef struct s_itx_grp
{
	t_itx arr[200];
	int count;
} t_itx_grp;

typedef struct s_ray
{
	t_point origin;
	t_vec4d direction;
} t_ray;

typedef struct s_camera
{
	bool is_set;
	int line_set;
	int hsize;
	int vsize;
	float fov;
	t_mat4d inv_transform;
	t_vec4d forward;
	t_vec4d up;
	t_vec4d left;
	t_mat4d rot;
	t_point from;
	t_vec4d scale;
	float half_width;
	float half_height;
	float half_view;
	float aspect_ratio;
	float pixel_size;
} t_camera;

typedef struct s_light
{
	int type;
	t_point pos;
	float ratio;
	t_color intensity;
	struct
	{
		t_vec4d orientation;
		float spot_angle;
	};
} t_light;

typedef struct s_scene
{
	bool refract_reflect;
	t_color ambiance;
	int num_a;
	int num_c;
	int shape_count;
	int light_count;
	int num_shapes;
	int num_lights;
	t_object *shapes;
	t_light *lights;
} t_scene;

#endif // !COMMON_H
