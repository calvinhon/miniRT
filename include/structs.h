/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:54:38 by marvin            #+#    #+#             */
/*   Updated: 2024/12/11 16:54:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libs/libft/libft.h"
# include "../libs/mlx_linux/mlx.h"
# include "../libs/mlx_macos/mlx.h"

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	double	p;
}	t_point;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
	double	p;
}	t_vector;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_ray
{
    t_point origin;
    t_vector direction;
} t_ray;

// Light source
typedef struct s_light
{
    t_point position;
    float   brightness;
    t_color color;
} t_light;

// Scene objects
typedef struct s_plane
{
    t_point point;   // A point on the plane
    t_vector normal;  // Normal vector to the plane
    t_color color;   // Color of the plane
} t_plane;

typedef struct s_sphere
{
    t_point center;
    float   radius;
    t_color color;
} t_sphere;

typedef struct s_cylinder
{
    t_point     base;     // base center of the cylinder
    t_vector    axis;     // axis vector (direction of the cylinder)
    float       radius;     // radius of the cylinder
    float       height;     // height of the cylinder
    t_color     color;    // color of the cylinder
} t_cylinder;

typedef struct s_cone
{
    t_point     apex;     // Apex of the cone
    t_vector    axis;     // Axis vector (direction of the cone)
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
    t_vector    direction;
    float       fov;
} t_camera;

typedef struct s_scene
{
    t_camera    camera;
    t_light     light;
    t_plane     plane;
    t_sphere    sphere;
    t_cylinder  cylinder;
    t_cone      cone;
    t_cube      cube;
    float       ambient;
    t_color     ambient_color;
}   t_scene;

typedef struct s_graphic
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		l_len;
	int		end;
}	t_graphic;

typedef struct s_threads
{
    int thread_id;
    int thread_count;
    int width;
    int height;
} t_threads;

typedef struct s_minirt
{
	//t_graphic	graphic;
	void	    *mlx;
	void	    *win;
	void	    *img;
	char	    *addr;
	int		    bpp;
	int		    l_len;
	int		    end;
	//t_scene	scene;
    t_camera    camera;
    t_light     *lights;
    void        *objs;

    float       ambient;
    t_color     ambient_color;
    //t_threads   threads;
    int         thread_id;
    int         thread_count;
    int         width;
    int         height;
}	t_minirt;

#endif