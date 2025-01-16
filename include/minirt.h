/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:54:48 by chon              #+#    #+#             */
/*   Updated: 2024/12/18 23:32:04 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MINIRT_H
# define MINIRT_H

# include "colors.h"
# include "draw.h"
# include "parsing.h"
# include "minirt_math.h"
# include <stdio.h>
# include <pthread.h>
# include <float.h>

void		set_controls(t_mlx_vars *env);
<<<<<<< HEAD
t_color		render_pixel(t_minirt *vars, int x, int y);
t_ray		cam_ray_to_pixel(t_camera *cam, int x, int y);
t_point		position(t_ray *r, float t);
t_ray		create_ray(t_point origin, t_vec4d);
=======

// Rays
t_point		position(t_ray *r, float t);
t_ray		create_ray(t_point *origin, t_vec4d *direction);
>>>>>>> 81bd0ab25fe8b8f98353709f500febd6c4c4c223
void		transform_ray(t_ray *r, t_mat4d *m);

// Intersections
bool		intersect_sphere(t_ray *r, t_object *sphere, t_itx_set *xs);
t_itx_set	intersect_world(t_scene *s, t_ray *r);
t_itx		*get_hit(t_itx_set *xs);
t_color		color_at(t_scene *s, t_ray *r, int depth);
t_color		render_pixel(t_minirt *program, int x, int y);

// Camera
t_camera	set_camera(float fov);
t_ray		cam_ray_to_pixel(t_camera *cam, int x, int y);
t_mat4d		view_transform(t_point from, t_point to, t_vec4d up);

// Lighting and Shading
t_vec4d		sphere_normal_at(t_object *o, t_point *wrld_p);
t_vec4d		reflect(t_vec4d *in, t_vec4d *normal);
t_color		lighting(t_material *material, t_light *l, t_comps *c, bool in_shadow);
t_color		shade_hit(t_scene *s, t_comps *comps, int depth);
bool		is_shadowed(t_scene *s, t_point *p, t_light *l);

#endif