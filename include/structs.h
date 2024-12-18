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

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	float	p;
}	t_point;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
	float	p;
}	t_vector;

typedef struct s_color
{
	int	t;
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}				t_ray;

// Scene structures
typedef struct s_ambient
{
	float	intensity;
	t_color	color;
}				t_ambient;

// Camera
typedef struct s_camera
{
	t_point		origin;
	t_vector	direction;
	float		fov;
}				t_camera;

// Light source
typedef struct s_light
{
	t_point		position;
	float		brightness;
	t_color		color;
}				t_light;

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
	t_point		point;
	t_vector	normal;
	t_color		color;
}				t_plane;

typedef struct s_sphere
{
	t_point		center;
	float		radius;
	t_color		color;
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

typedef struct s_graphic
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		l_len;
	int		end;
}				t_graphic;

typedef struct s_threads
{
	int		thread_id;
	int		thread_count;
	int		width;
	int		height;
}				t_threads;

typedef struct s_minirt
{
	t_graphic	graphic;
	t_scene		scene;
	t_threads	*threads;
}				t_minirt;
#endif