/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:35:52 by nth          #+#    #+#             */
/*   Updated: 2024/10/16 13:18:51 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "keys.h"
# include "macros.h"
# include "lag.h"
# include "common.h"
# include <pthread.h>
# include <stdint.h> // for `uint32_t`
# include "libft.h" // for `t_split`
# include <stdio.h> //// TEMP
# include <sys/time.h>

# ifdef EPSILON
#  undef EPSILON
#  define EPSILON 0.0001f
# endif // !EPSILON

#define GL_SILENCE_DEPRECATION

long long	my_gettime(void);

typedef struct s_frame
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		bpp_8;
	int		line_length;
	int		endian;
	int		tex_width;
	int		tex_height;
}	t_frame;

typedef struct s_core	t_core;

typedef struct s_tex_frame
{
	char		*name;
	t_frame		*fra_tex;
}	t_tex_frame;

typedef struct s_minirt
{
	int			error_code;
	char		*data;
	int			flt_operations;
	void		*mlx;
	void		*win;
	t_list		*textures;
	t_frame		frame;
	t_scene		scene;
	t_camera	cam;
	t_core		*cores;
	bool		stop;
	float		delta_time;
	struct s_select
	{
		bool	is_cam;
		t_object	*object;
		t_vec4s	ray_dir;
	}	selected;
	struct s_ambient
	{
		bool	is_set;
		int		line_set;
		t_color	color;
		float	ratio;
	}	ambiance;
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
		bool		leftctrl;
		bool		leftshift;
	}	move;
	struct s_mouse
	{
		bool		left_click;
	}	mouse;
}	t_minirt;

struct s_core
{
	int				id;
	pthread_t		thread;
	t_minirt		*minirt;
	int				y;
	int				yend;
	int				x;
	int				xend;
	bool			work_ready;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
};

typedef struct s_itx_data
{
	bool		shadowed;
	double		t;
	t_object		*obj;
	t_vec4s		p;
	t_vec4s		over_point;
	t_vec4s		under_point;
	t_vec4s		eyev;
	t_vec4s		normalv;
	t_vec4s		reflectv;
	int			inside;
	double		n1;
	double		n2;
}	t_itx_data;

/*--- PARSING ---*/

typedef struct s_validate_atof
{
	size_t	sign_count;
	size_t	dot_count;
	size_t	digit_count;
	bool	found_alpha;
}	t_vatof;

bool		is_normalised(t_vec4s *vec, size_t i, t_minirt *minirt);
//float		ft_atof(char *rep, t_minirt *minirt);
float		ft_atof(const char *str);

// Parsing
void	parse(char *file, t_minirt *minirt);
void	parse_data(t_minirt *minirt, char *data, size_t total_size);

void	parse_ambient(t_minirt *minirt, char *data, size_t *i);
t_color	parse_color(char *data, size_t *i, t_minirt *minirt);
float	parse_float(char *data, size_t *i);
int		parse_int(char *data, size_t *i);

void	parse_camera(t_minirt *minirt, char *data, size_t *i);
t_vec4s	parse_point(char *data, size_t *i);
t_vec4s	parse_vector(char *data, size_t *i);

void	parse_camera(t_minirt *minirt, char *data, size_t *i);
void	parse_light(t_minirt *minirt, char *data, size_t *i);
void	parse_spotlight(t_minirt *minirt, char *data, size_t *i);

bool	parse_plane(t_minirt *minirt, char *data, size_t *i, size_t idx);
bool	parse_sphere(t_minirt *minirt, char *data, size_t *i, size_t idx);
bool	parse_cylinder(t_minirt *minirt, char *data, size_t *i, size_t idx);
bool	parse_cube(t_minirt *minirt, char *data, size_t *i, size_t idx);
bool	parse_cone(t_minirt *minirt, char *data, size_t *i, size_t idx);

void	parse_material(t_material *material, char *data, size_t *i, t_minirt *minirt);
bool 	parse_bump_xpm(t_material *material, char *data, size_t *i, t_minirt *minirt);
void	set_material(t_material *material, char *data, size_t *i, t_minirt *minirt);
//bool		parse(const char *filename, t_minirt *minirt);
//bool		parse_ambient(t_minirt *minirt, t_split *fields, int curr_line);
//bool		parse_light(t_minirt *minirt, const t_split *fields,
//				int curr_line);
//bool		parse_spot_light(t_minirt *minirt, const t_split *fields,
//				int curr_line);
//bool		parse_camera(t_minirt *minirt, const t_split *fields,
//				int curr_line);
//bool		parse_sphere(t_minirt *minirt, const t_split *fields,
//				int curr_line);
//bool		parse_plane(t_minirt *minirt, const t_split *fields,
//				int curr_line);
//bool		parse_cube(t_minirt *minirt, const t_split *fields,
//				int curr_line);
//bool		parse_cylinder(t_minirt *minirt, const t_split *fields,
//				int curr_line);
//bool		parse_cone(t_minirt *minirt, const t_split *fields,
//				int curr_line);
//bool		parse_color(t_color *color, char *str, int curr_line);
//bool		parse_vec4v(t_vec4s *vec, char *str, t_minirt *minirt,
//				int curr_line);
//bool		parse_vec4p(t_vec4s *vec, char *str, t_minirt *minirt,
//				int curr_line);
//bool		parse_single_f(float *f, char *str, t_minirt *minirt,
//				int curr_line);
//bool		parse_material(t_material *obj_material, char **material_fields,
//				t_minirt *minirt, int curr_line);
//bool		parse_plane_checker(t_material *obj_mat, t_minirt *minirt,
//				char *is_checker);
//bool		parse_bump_xpm(t_material *obj_mat, t_minirt *minirt,
//				char *filename);
t_mat4s		rt_extract_rot_vertical(const t_vec4s u);
t_mat4s		rt_get_cam_inverse(const t_mat4s *view);
//bool		check_object_validity_init(t_minirt *minirt, const char *info,
//				int curr_line, const t_split fields);
//void		parse_fatal_msg(char *msg, int curr_line);
//void		parse_warn_msg(char *msg, char *expected, int curr_line, bool ign);
//void		parse_err_msg(char *msg, char *expected, int curr_line);
//void		parse_syn_err_msg(char *msg, int curr_line);

/*--- RENDERING ---*/

t_color		rt_render_pixel(t_minirt *minirt, int x, int y);
t_ray		ray_for_pixel(const t_camera *cam, int px, int py);
bool		make_window(t_minirt *minirt, int width, int height);
void		put_pixel(t_frame *frame, int x, int y, const t_color *color);
void		render_frame(t_minirt *current_context);
t_color		color_at(t_scene *w, t_ray *r, int depth);

/*---- THREADS ----*/

bool		ini_core(t_minirt *minirt);
bool		thread_arbiter(t_minirt *minirt);
void		*await_task(void *arg);
void		interpolate_horizontal(t_core const *data);
void		interpolate_vertical(t_core const *data);
int			cdiff(t_color a, t_color b);
t_color		lerp_colors(const t_color *a, const t_color *b, float t);
t_color		fetch_pixel_color(const t_frame *frame, int x, int y);

/*--- STATE ---*/

//void		update_camera_state(t_camera *camera);
int			update_rt(t_minirt *minirt);
int			update_minirt(t_minirt *minirt);
int			record_keypress(int keycode, t_minirt *minirt);
int			record_keyrelease(int keycode, t_minirt *minirt);
int			select_shape(int button, int x, int y, void *minirt);

/*--- EVENTS ---*/
void		object_controls(t_minirt *state);
void		camera_controls(t_minirt *state);
void		camera_rotations(t_minirt *state);
t_mat4s		rt_rotation_matrix_from_axis_angle(const t_vec4s *axis,
				float angle);

/*--- DESTROY ---*/
void		errors(int err_code, char* err_ms, void *ptr);
void		destroy_mlx(t_minirt *minirt);
void		destroy_scene(t_minirt *minirt);
int			destroy_minirt(t_minirt *minirt);
void		destroy_textures(t_minirt *minirt);
void		destroy_2d_arr(char **arr);
void		free_minirt(t_minirt *minirt);

/*--- RAY - MANIPULATION ---*/

void		ray_create(t_ray *ray, t_vec4s *origin, t_vec4s *direction);
void		ray_position(t_vec4s *result, const t_ray *ray, float t);
void		ray_transform(t_ray *ray, const t_mat4s *matrix);
t_vec4s		reflect(t_vec4s *in, t_vec4s *normal);

/*--- FRAGMENT CALCULATION ---*/

t_itx_grp	intersect_world(t_scene *w, t_ray *r);
bool		intersect_sphere(t_ray *r, t_object *sphere, t_itx_grp *xs);
bool		intersect_plane(t_ray *ray, t_object *plane, t_itx_grp *xs);
bool		intersect_cylinder(t_ray *ray, t_object *cy, t_itx_grp *xs);
bool		intersect_cube(t_ray *ray, t_object *cube, t_itx_grp *xs);
bool		intersect_cone(t_ray *ray, t_object *cone, t_itx_grp *xs);
t_vec4s		cone_normal_at(t_object *cone, t_vec4s *world_point);
t_vec4s		cube_normal_at(t_object *cube, t_vec4s *world_point);
t_vec4s		cylinder_normal_at(t_object *cylinder, t_vec4s *world_point);
void		cast_shadow_ray(t_scene *w, t_ray *r, t_itx_grp *xs);
t_vec4s		plane_normal_at(t_object *plane, t_vec4s *world_p);
t_vec4s		sphere_normal_at(t_object *sphere, t_vec4s *world_p);
void		quick_sort_intersections(t_itx *arr, size_t size);
t_itx		*get_hit(t_itx_grp *xs);
void		transpose_mat4s(const t_mat4s *m, t_mat4s *out);

/*--- TEXTURES ---*/

t_frame		*rt_xpm_file_to_canvas(char *filepath, void *mlx);
t_vec2s		rt_get_sphere_uv_local(t_vec4s *hitp);
t_vec2s		rt_get_plane_uv_local(t_vec4s *hitp, t_vec4s tangent,
				t_vec4s *normal);
t_vec4s		rt_get_sphere_tangent(t_vec4s *local_normal);
t_vec4s		rt_get_plane_tangent(t_vec4s *local_normal);
t_vec2s		rt_get_cylinder_uv_local(t_vec4s *hitp);
t_vec4s		rt_get_cylinder_tangent(t_vec4s *local_normal, t_object *cylinder);
t_color		rt_sample_texture(const t_frame *fra_tex, const t_vec2s *uv);
t_vec4s		rt_apply_normal_map(const t_object *obj, const t_vec2s *uv,
				const t_vec4s *local_normal, const t_vec4s *tangent);

/*--- LIGHTING ---*/

t_color		shade_hit(t_scene *scene, t_itx_data *comps, int depth);
t_color		check_for_refref(t_scene *scene, t_itx_data *comps, int depth);
bool		is_shadowed(t_scene *scene, t_vec4s *point, t_light *light);
void		prepare_refractions(t_itx *hit, t_itx_data *comps,
				t_itx_grp *itxs);
t_color		refracted_color(t_scene *scene, t_itx_data *comps,
				int depth);
t_color		reflected_color(t_scene *scene, t_itx_data *comps,
				int depth);
float		schlick(t_itx_data *comps);
t_color		lighting(t_itx_data *comps, t_material *material, t_light *light,
				bool in_shadow);
float		get_spot_light_intensity(t_light *light, t_vec4s light_v);
bool		is_spot_light_shadowed(t_light *light, t_vec4s *v);
void		check_for_texture(t_itx_data *comps, t_material *material,
				t_material_colors *mat_colors);

#endif // !MINIRT_H
