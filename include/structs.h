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

# include "../libs/libft/libft.h"
# include "../libs/mlx_linux/mlx.h"
# include "../libs/mlx_macos/mlx.h"
# include <threads.h>

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	float	p;
}	t_point;

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
}	t_vec4d;

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

typedef struct s_color
{
	int		t;
	float	r;
	float	g;
	float	b;
}				t_color;

typedef struct s_ray
{
	t_point		origin;
	t_vec4d	direction;
}				t_ray;

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
	t_point		origin;
	t_vec4d	direction;
	float		fov;
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
	t_vec4d	normal;
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
	t_vec4d	axis;
	float		radius;
	float		height;
	t_color		color;
}				t_cylinder;

typedef struct s_cone
{
	t_point		apex;
	t_vec4d	axis;
	float		angle;
	t_color		color;
}				t_cone;

typedef struct s_cube
{
	t_point		center;
	float		size;
	t_vec4d	rotation;
	t_color		color;
}				t_cube;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		*light;
	size_t		l;
	size_t		idx_l;
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
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		l_len;
	int		end;
}	t_mlx_vars;

typedef struct s_minirt t_minirt;

typedef struct s_thread
{
	int			id;
	int			count;
	int			width;
	int			height;
	pthread_t	*th;
}				t_threads;

typedef struct s_minirt
{
	t_mlx_vars	graphic;
	t_scene		scene;
	pthread_t	*threads;
}				t_minirt;

#endif