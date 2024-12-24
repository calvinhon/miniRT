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
<<<<<<< HEAD
# include <threads.h>
=======
# include <pthread.h>
>>>>>>> fac9762a1543c7c015675c63cef213e9d71331ec

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
<<<<<<< HEAD
	float	x;
	float	y;
	float	z;
	float	p;
}	t_vector;
=======
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
>>>>>>> math

typedef struct s_color
{
	int	t;
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_ray
{
<<<<<<< HEAD
	t_point		origin;
	t_vector	direction;
}				t_ray;

// Ambient
typedef struct s_ambient
{
	float	intensity;
	t_color	color;
}				t_ambient;
=======
    t_point origin;
    t_vec4d direction;
} t_ray;
>>>>>>> math

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
	t_vector	direction;
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
	float		shininess;
}				t_object;

// Scene objects
typedef struct s_plane
{
<<<<<<< HEAD
	t_point		point;
	t_vector	normal;
	t_color		color;
}				t_plane;
=======
    t_point point;   // A point on the plane
    t_vec4d normal;  // Normal vector to the plane
    t_color color;   // Color of the plane
} t_plane;
>>>>>>> math

typedef struct s_sphere
{
	t_point		center;
	float		radius;
	t_color		color;
}				t_sphere;

typedef struct s_cylinder
{
<<<<<<< HEAD
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
=======
    t_point     base;     // base center of the cylinder
    t_vec4d    axis;     // axis vector (direction of the cylinder)
    float       radius;     // radius of the cylinder
    float       height;     // height of the cylinder
    t_color     color;    // color of the cylinder
} t_cylinder;

typedef struct s_cone
{
    t_point     apex;     // Apex of the cone
    t_vec4d    axis;     // Axis vector (direction of the cone)
    float       angle;      // Half-angle of the cone in radians
    t_color     color;    // Color of the cone
}               t_cone;

typedef struct s_cube
{
    t_point min;      // Minimum corner of the cube
    t_point max;      // Maximum corner of the cube
    t_color color;    // Color of the cube
} t_cube;

typedef struct s_camera
{
    t_point     origin;
    t_vec4d    direction;
    float       fov;
} t_camera;
>>>>>>> math

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
<<<<<<< HEAD
}				t_graphic;
=======
}	t_mlx_vars;
>>>>>>> math

typedef struct s_minirt t_minirt;

typedef struct s_thread
{
<<<<<<< HEAD
	int			id;
	int			count;
	int			width;
	int			height;
	pthread_t	*th;
}				t_threads;
=======
	int				id;
	pthread_t		thread;
	t_minirt		*minirt;
	int				y;
	int				y_f;
	int				x;
	int				x_f;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}	t_thread;
>>>>>>> fac9762a1543c7c015675c63cef213e9d71331ec

typedef struct s_minirt
{
	t_graphic	graphic;
	t_scene		scene;
<<<<<<< HEAD
	pthread_t	*threads;
=======
	t_thread	*comp_units;
>>>>>>> fac9762a1543c7c015675c63cef213e9d71331ec
}				t_minirt;

#endif