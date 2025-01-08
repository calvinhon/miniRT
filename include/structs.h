/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:54:38 by marvin            #+#    #+#             */
/*   Updated: 2024/12/19 00:05:12 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef STRUCTS_H
# define STRUCTS_H

// # include "../libs/libft/libft.h"
// # include "../libs/mlx_linux/mlx.h"
// # include "../libs/mlx_macos/mlx.h"
# include <pthread.h>
# include <immintrin.h> //__m256d, __m128)
# include <stdint.h> // bit-wise & integer types
# include <stdbool.h> // boolean types

typedef struct s_point
{
	struct
	{
		float	x;
		float	y;
		float	z;
		float	p;
	};
	float		p[4];
	uint32_t	pint[4];
	__m128		psimd;
}__attribute((aligned(16))) t_point;

typedef struct s_vector
{
	struct
	{
		float	a;
		float	b;
		float	c;
		float	v;
	};
	float		v[4];
	uint32_t	vint[4];
	__m128		vsimd;
}__attribute((aligned(16))) t_vector;

typedef struct s_color
{
	struct
	{
		float	t;
		float	g;
		float	b;
		float	t;
	};
	t_vector	v;
}		t_color;

typedef struct s_vec2d
{
	double	x;
	double	y;
}	t_vec2d;

typedef struct s_vec3d
{
	double	x;
	double	y;
	double	z;
}	t_vec3d;

typedef struct s_vec4d
{
	double	x;
	double	y;
	double	z;
	double	p;
}	t_vector;

typedef struct s_shear
{
	double	x_y;
	double	x_z;
	double	y_x;
	double	y_z;
	double	z_x;
	double	z_y;
}	t_shear;


typedef struct s_mat2d
{
	double 	matrix[4];
}	t_mat2d;

typedef struct s_mat3d
{
	double 	matrix[9];
}	t_mat3d;

typedef struct s_mat4d
{
	double	matrix[16];
}	t_mat4d;


typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}				t_ray;
//
typedef struct s_itx
{
	float		t;
	t_object	*object;
	float		n1;
	float		n2;
}	t_itx;
//
typedef struct s_itx_set
{
	t_itx	arr[200];
	int		count;
}	t_itx_set;


// Ambient
typedef struct s_ambient
{
	float	intensity;
	t_color	color;
}				t_ambient;

typedef struct s_material
{
	t_color		color;
	t_ambient	ambient;
	t_color		diffuse;
	t_color		specular;
	float		shininess;
}	t_material;

// Light source
typedef struct s_light
{
	t_point		position;
	float		brightness;
	t_color		color;
}				t_light;

// Camera
typedef struct s_camera
{
	bool		ini;
	t_point		origin;
	t_vector	direction;
	float		fov;
	int			hsize;
	int			vsize;

}				t_camera;

// Object types
typedef enum e_objtype
{
	SPHERE,
	CYLINDER,
	PLANE,
	CUBE,
	CONE
}			t_objtype;

// data for objects

// Material = data for object
typedef struct s_material
{
	t_color		color;
	t_color		xordc;
	float		ambient;
	float		diffuse;
	float		specular;
	float		sheen;
	float		reflective;
	float		transparency;
	float		refractive_index;
	bool		checkered;
	t_mlx_vars	*graphic;
}	t_material;



// Generic object structure
typedef struct s_object
{
	t_objtype	type;
	void		*data;
	float		reflection;
	t_material	material;
}				t_object;

// Scene objects
typedef struct s_plane
{
	t_point		point;
	t_vector	normal;
	t_color		color;
}				t_plane;

typedef struct s_sphere
{
	t_point		center;
	double		radius;
	t_color		color;
	t_mat4d		transform;
	t_material	material;
}				t_sphere;

typedef struct s_cylinder
{
	t_point		base;
	t_vector	axis;
	float		radius;
	float		height;
	t_color		color;
}				t_cylinder;

typedef struct s_cone
{
	t_point		apex;
	t_vector	axis;
	float		angle;
	t_color		color;
}				t_cone;

typedef struct s_cube
{
	t_point		center;
	float		size;
	t_vector	rotation;
	t_color		color;
}				t_cube;

typedef struct s_scene
{
	bool		refract_reflect;
	t_ambient	ambient;
	t_camera	camera;
	size_t		l;
	size_t		idx_l;
	t_light		*light;
	t_object	*objs;
	size_t		n_objs;
	size_t		idx_obj;
	size_t		a;
	size_t		c;
	size_t		pl;
	size_t		sp;
	size_t		cy;
	size_t		cu;
	size_t		co;

}				t_scene;

typedef struct s_mlx_vars
{
	void	*img;
	char	*addr;
	int		bpp;
	int		l_len;
	int		end;
}	t_mlx_vars;

typedef struct s_minirt t_minirt;

typedef struct s_unit
{
	int				id;
	pthread_t		thread;
	t_minirt		*minirt;
	int				y;
	int				y_f;
	int				x;
	int				x_f;
	bool			ready;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}				t_unit;

typedef struct s_texture
{
	char		*name;
	t_mlx_vars	*tex;
}	t_texture;

typedef struct s_minirt
{
	//t_mlx_vars	graphic;
	void		*mlx;
	void		*win;
	t_mlx_vars	frame;
	// t_camera	cam;
	t_scene		scene;
	t_unit		*units;
	t_list		*textures;
	int			error;
	bool		stop;
	float 		time;

	// moving object
	bool		is_cam;
	t_object	*obj;
	t_vector	ray_dir;

	struct s_move
	{
		bool		w;
		bool		a;
		bool		s;
		bool		d;
		bool		up;
		bool		down;
		bool		left;
		bool		right;
		bool		space;
		bool		lctrl;
		bool		lshift;
	}	move;

	struct s_mouse
	{
		bool		left_click;
	}	mouse;

}				t_minirt;

#endif