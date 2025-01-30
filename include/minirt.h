/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nthoach <nthoach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:54:48 by chon              #+#    #+#             */
/*   Updated: 2024/12/18 23:32:04 by nthoach          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MINIRT_H
#define MINIRT_H

#include "libft.h"
#include "mlx.h"
#include "mlx.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>
#include "keys.h"
#include "macros.h"
#include "common.h"
#include "miniRT_math.h"
#include "colors.h"

#define GL_SILENCE_DEPRECATION

long long my_gettime(void);

typedef struct s_frame
{
	void *ptr;
	char *addr;
	int bpp;
	int bpp_8;
	int line_length;
	int endian;
	int tex_width;
	int tex_height;
} t_frame;

typedef struct s_core t_core;

typedef struct s_tex_frame
{
	char *name;
	t_frame *fra_tex;
} t_tex_frame;

typedef struct s_minirt
{
	int error_code;
	char *data;
	int flt_operations;
	void *mlx;
	void *win;
	t_list *textures;
	t_frame frame;
	t_scene scene;
	t_camera cam;
	t_core *cores;
	bool stop;
	float delta_time;
	struct s_select
	{
		bool is_cam;
		t_object *object;
		t_vec4d ray_dir;
	} selected;
	struct s_ambient
	{
		bool is_set;
		int line_set;
		t_color color;
		float ratio;
	} ambiance;
	struct s_move
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
		bool leftctrl;
		bool leftshift;
	} move;
	struct s_mouse
	{
		bool left_click;
	} mouse;
} t_minirt;

typedef struct s_core
{
	int id;
	pthread_t thread;
	t_minirt *minirt;
	int y;
	int yend;
	int x;
	int xend;
	bool work_ready;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}	t_core;

typedef struct s_computations_for_xs
{
	bool shadowed;
	double t;
	t_object *obj;
	t_point p;
	t_point over_point;
	t_point under_point;
	t_vec4d eye_v;
	t_vec4d normal_v;
	t_vec4d reflect_v;
	t_color ambient;
	t_color diffuse;
	t_color specular;
	t_color l_color;
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

bool is_normalised(t_vec4d *vec, size_t i, t_minirt *minirt);
// float		ft_atof(char *rep, t_minirt *minirt);
float ft_atof(const char *str);

// Parsing
void parse(char *file, t_minirt *minirt);
void parse_data(t_minirt *minirt, char *data, size_t total_size);

void parse_ambient(t_minirt *minirt, char *data, size_t *i);
t_color parse_color(char *data, size_t *i, t_minirt *minirt);
float parse_float(char *data, size_t *i);
int parse_int(char *data, size_t *i);

void parse_camera(t_minirt *minirt, char *data, size_t *i);
t_point parse_point(char *data, size_t *i);
t_vec4d parse_vector(char *data, size_t *i);

void parse_camera(t_minirt *minirt, char *data, size_t *i);
void parse_light(t_minirt *minirt, char *data, size_t *i);
void parse_spotlight(t_minirt *minirt, char *data, size_t *i);

bool parse_plane(t_minirt *minirt, char *data, size_t *i, size_t idx);
bool parse_sphere(t_minirt *minirt, char *data, size_t *i, size_t idx);
bool parse_cylinder(t_minirt *minirt, char *data, size_t *i, size_t idx);
bool parse_cube(t_minirt *minirt, char *data, size_t *i, size_t idx);
bool parse_cone(t_minirt *minirt, char *data, size_t *i, size_t idx);

void	parse_material(t_material *material, char *data, size_t *i, t_minirt *minirt);
bool	parse_bump_xpm(t_material *material, char *data, size_t *i, t_minirt *minirt);
void	set_material(t_material *material, char *data, size_t *i, t_minirt *minirt);
bool	parse_pattern(t_material *material, char *data,	size_t *i, t_minirt *minirt);
// bool		parse(const char *filename, t_minirt *minirt);
// bool		parse_ambient(t_minirt *minirt, t_split *fields, int curr_line);
// bool		parse_light(t_minirt *minirt, const t_split *fields,
//				int curr_line);
// bool		parse_spot_light(t_minirt *minirt, const t_split *fields,
//				int curr_line);
// bool		parse_camera(t_minirt *minirt, const t_split *fields,
//				int curr_line);
// bool		parse_sphere(t_minirt *minirt, const t_split *fields,
//				int curr_line);
// bool		parse_plane(t_minirt *minirt, const t_split *fields,
//				int curr_line);
// bool		parse_cube(t_minirt *minirt, const t_split *fields,
//				int curr_line);
// bool		parse_cylinder(t_minirt *minirt, const t_split *fields,
//				int curr_line);
// bool		parse_cone(t_minirt *minirt, const t_split *fields,
//				int curr_line);
// bool		parse_color(t_color *color, char *str, int curr_line);
// bool		parse_vec4v(t_vec4d *vec, char *str, t_minirt *minirt,
//				int curr_line);
// bool		parse_vec4p(t_vec4d *vec, char *str, t_minirt *minirt,
//				int curr_line);
// bool		parse_single_f(float *f, char *str, t_minirt *minirt,
//				int curr_line);
// bool		parse_material(t_material *obj_material, char **material_fields,
//				t_minirt *minirt, int curr_line);
// bool		parse_plane_checker(t_material *obj_mat, t_minirt *minirt,
//				char *is_checker);
// bool		parse_bump_xpm(t_material *obj_mat, t_minirt *minirt,
//				char *filename);
t_mat4d rt_extract_rot_vertical(const t_vec4d u);
t_mat4d rt_get_cam_inverse(const t_mat4d *view);
// bool		check_object_validity_init(t_minirt *minirt, const char *info,
//				int curr_line, const t_split fields);
// void		parse_fatal_msg(char *msg, int curr_line);
// void		parse_warn_msg(char *msg, char *expected, int curr_line, bool ign);
// void		parse_err_msg(char *msg, char *expected, int curr_line);
// void		parse_syn_err_msg(char *msg, int curr_line);

/*--- RENDERING ---*/
bool make_window(t_minirt *minirt, int width, int height);
t_camera set_camera(float fov);
t_ray cam_ray_to_pixel(const t_camera *cam, int x, int y);
t_mat4d view_transform(t_point from, t_point to, t_vec4d up);
void put_pixel(t_frame *frame, int x, int y, t_color *color);
t_color render_pixel(t_minirt *program, int x, int y);
// t_color		render_pixel(t_minirt *minirt, int x, int y);
// t_ray		ray_for_pixel(const t_camera *cam, int px, int py);
// bool		make_window(t_minirt *minirt, int width, int height);
// void		render_frame(t_minirt *current_context);
// t_color		color_at(t_scene *w, t_ray *r, int depth);

/*---- THREADS ----*/

bool init_core(t_minirt *minirt);
bool thread_arbiter(t_minirt *minirt);
void *await_task(void *arg);
void	interpolate_horizontal(t_core const *data);
void	interpolate_vertical(t_core const *data);
int		cdiff(t_color a, t_color b);
t_color lerp_colors(const t_color *a, const t_color *b, float t);
t_color fetch_pixel_color(const t_frame *frame, int x, int y);

/*--- STATE ---*/
void update_camera_state(t_camera *camera);
int update_rt(t_minirt *minirt);
int update_minirt(t_minirt *minirt);
int record_keypress(int keycode, t_minirt *minirt);
int record_keyrelease(int keycode, t_minirt *minirt);
int select_shape(int button, int x, int y, void *minirt);

/*--- EVENTS ---*/
void object_controls(t_minirt *state);
void camera_controls(t_minirt *state);
void camera_rotations(t_minirt *state);
t_mat4d rt_rotation_matrix_from_axis_angle(const t_vec4d *axis,
										   float angle);

/*--- DESTROY ---*/
void errors(int err_code, char *err_ms, void *ptr);
void destroy_mlx(t_minirt *minirt);
void destroy_scene(t_minirt *minirt);
int destroy_minirt(t_minirt *minirt);
void destroy_textures(t_minirt *minirt);
void destroy_2d_arr(char **arr);
void free_minirt(t_minirt *minirt);

/*--- RAY - MANIPULATION ---*/
t_point position(t_ray *r, float t);
t_ray create_ray(t_point *origin, t_vec4d *direction);
void transform_ray(t_ray *r, t_mat4d *m);
// void		ray_create(t_ray *ray, t_vec4d *origin, t_vec4d *direction);
// void		ray_position(t_vec4d *result, const t_ray *ray, float t);
// void		ray_transform(t_ray *ray, const t_mat4d *matrix);
// t_vec4d		reflect(t_vec4d *in, t_vec4d *normal);

/*--- TEXTURES ---*/

t_frame *rt_xpm_file_to_canvas(char *filepath, void *mlx);
t_vec2d rt_get_sphere_uv_local(t_vec4d *hitp);
t_vec2d rt_get_plane_uv_local(t_vec4d *hitp, t_vec4d tangent,
							  t_vec4d *normal);
t_vec4d rt_get_sphere_tangent(t_vec4d *local_normal);
t_vec4d rt_get_plane_tangent(t_vec4d *local_normal);
t_vec2d rt_get_cylinder_uv_local(t_vec4d *hitp);
t_vec4d rt_get_cylinder_tangent(t_vec4d *local_normal, t_object *cylinder);
t_color rt_sample_texture(const t_frame *fra_tex, const t_vec2d *uv);
t_vec4d rt_apply_normal_map(const t_object *obj, const t_vec2d *uv,
							const t_vec4d *local_normal, const t_vec4d *tangent);

/*--- LIGHTING ---*/
t_vec4d reflect(t_vec4d *in, t_vec4d *normal);
t_color lighting(t_material *m, t_light *l, t_comps *c, t_color *ambiance);
t_color shade_hit(t_scene *s, t_comps *comps, int depth);
bool is_shadowed(t_scene *s, t_point *p, t_light *l);
// t_color		shade_hit(t_scene *scene, t_comps *comps, int depth);
// t_color		check_for_refref(t_scene *scene, t_comps *comps, int depth);
// bool		is_shadowed(t_scene *scene, t_vec4d *point, t_light *light);
// void		prepare_refractions(t_itx *hit, t_comps *comps,
// 				t_itx_grp *itxs);
// t_color		refracted_color(t_scene *scene, t_comps *comps,
// 				int depth);
// t_color		reflected_color(t_scene *scene, t_comps *comps,
// 				int depth);
// float		schlick(t_comps *comps);
// t_color		lighting(t_comps *comps, t_material *material, t_light *light,
// 				bool in_shadow);
// float		get_spot_light_intensity(t_light *light, t_vec4d light_v);
// bool		is_spot_light_shadowed(t_light *light, t_vec4d *v);
// void		check_for_texture(t_comps *comps, t_material *material,
// 				t_material_colors *mat_colors);

/*--- INTERSECTIONS ---*/
t_itx_grp local_intersect(t_scene *s, t_ray *r);
t_itx *get_hit(t_itx_grp *xs);
t_color color_at(t_scene *s, t_ray *r, int depth);
t_color render_pixel(t_minirt *program, int x, int y);
void intersect_sphere(t_ray *r, t_object *sphere, t_itx_grp *xs);
t_vec4d sphere_normal_at(t_object *o, t_point *wrld_p);
void intersect_plane(t_ray *r, t_object *o, t_itx_grp *xs);
t_vec4d plane_normal_at(t_object *o, t_point *wrld_p);
void intersect_cylinder(t_ray *r, t_object *o, t_itx_grp *xs);
t_vec4d cylinder_normal_at(t_object *o, t_point *wrld_p);

/*--- PATTERNS ---*/
t_color pattern_at(t_object *o, t_point *world_point, t_pattern *pattern);
float perlin_noise(float x, float y, float z);

#endif