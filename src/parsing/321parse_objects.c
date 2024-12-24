/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   321parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD:src/parsing/321parse_objects.c
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:32:20 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/20 13:56:01 by marvin           ###   ########.fr       */
=======
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:32:20 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/21 14:37:24 by honguyen         ###   ########.fr       */
>>>>>>> fac9762a1543c7c015675c63cef213e9d71331ec:src/parsing/322parse_objects.c
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	parse_bonus(t_minirt *minirt, char *data, \
				size_t *i, size_t idx)
{
	minirt->scene.objs[idx].reflection = parse_float(data, i);
	minirt->scene.objs[idx].shininess = parse_float(data, i);
}

void	*allocate_obj(t_minirt *minirt, t_objtype type, size_t idx)
{
	minirt->scene.objs[idx].type = type;
	if (type == SPHERE)
		minirt->scene.objs[idx].data = malloc(sizeof(t_sphere));
	else if (type == PLANE)
		minirt->scene.objs[idx].data = malloc(sizeof(t_plane));
	else if (type == CYLINDER)
		minirt->scene.objs[idx].data = malloc(sizeof(t_cylinder));
	else if (type == CUBE)
		minirt->scene.objs[idx].data = malloc(sizeof(t_cube));
	else if (type == CONE)
		minirt->scene.objs[idx].data = malloc(sizeof(t_cone));
	else
		errors(ER_OBJ_TYPE, minirt);
	if (!minirt->scene.objs[idx].data)
		errors(ER_MALLOC, minirt);
	return (minirt->scene.objs[idx].data);
}

void	parse_plane(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_plane	*plane;

	plane = (t_plane *)allocate_obj(minirt, PLANE, idx);
	(*i) += 2;
	plane->point = parse_point(data, i);
	plane->normal = parse_vector(data, i);
	plane->color = parse_color(data, i);
<<<<<<< HEAD:src/parsing/321parse_objects.c
	#if BONUS
		minirt->scene.objs[idx].reflection = parse_float(data, i);
		minirt->scene.objs[idx].shininess = parse_float(data, i);
	#endif
=======
	if (BONUS)
		parse_bonus(minirt, data, i, idx);
>>>>>>> fac9762a1543c7c015675c63cef213e9d71331ec:src/parsing/322parse_objects.c
}

void	parse_sphere(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)allocate_obj(minirt, SPHERE, idx);
	(*i) += 2;
	sphere->center = parse_point(data, i);
	sphere->radius = parse_float(data, i);
	sphere->color = parse_color(data, i);
<<<<<<< HEAD:src/parsing/321parse_objects.c
	#if BONUS
		minirt->scene.objs[idx].reflection = parse_float(data, i);
		minirt->scene.objs[idx].shininess = parse_float(data, i);
	#endif
=======
	if (BONUS)
		parse_bonus(minirt, data, i, idx);
>>>>>>> fac9762a1543c7c015675c63cef213e9d71331ec:src/parsing/322parse_objects.c
}

void	parse_cylinder(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)allocate_obj(minirt, CYLINDER, idx);
	(*i) += 2;
	cylinder->base = parse_point(data, i);
	cylinder->axis = parse_vector(data, i);
	cylinder->radius = parse_float(data, i);
	cylinder->height = parse_float(data, i);
	cylinder->color = parse_color(data, i);
<<<<<<< HEAD:src/parsing/321parse_objects.c
	#if BONUS
		minirt->scene.objs[idx].reflection = parse_float(data, i);
		minirt->scene.objs[idx].shininess = parse_float(data, i);
	#endif
}

void	parse_cone(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_cone	*cone;

	cone = (t_cone*) allocate_obj(minirt, CONE, idx);
	(*i) += 2;
	cone->apex = parse_point(data, i);
	cone->axis = parse_vector(data, i);
	cone->angle = parse_float(data, i);
	cone->color = parse_color(data, i);
	#if BONUS
		minirt->scene.objs[idx].reflection = parse_float(data, i);
		minirt->scene.objs[idx].shininess = parse_float(data, i);
	#endif
}

void	parse_cube(t_minirt *minirt, char *data, size_t *i, size_t idx)
{
	t_cube	*cube;

	cube = (t_cube*) allocate_obj(minirt, CUBE, idx);
	(*i) += 2;
	cube->center = parse_point(data, i);
	cube->size = parse_float(data, i);
	cube->rotation = parse_vector(data, i);	
	cube->color = parse_color(data, i);
	#if BONUS
		minirt->scene.objs[idx].reflection = parse_float(data, i);
		minirt->scene.objs[idx].shininess = parse_float(data, i);
	#endif
}

void	parse_object(t_minirt *minirt, char *data, size_t *i)
{
	size_t	start;
	size_t	idx;

	idx = minirt->scene.idx_obj++;
	start = *i;
	if (data[start] == 'p' && data[start + 1] == 'l')
		parse_plane(minirt, data, i, idx);
	else if (data[start] == 's' && data[start + 1] == 'p')
		parse_sphere(minirt, data, i, idx);
	else if (data[start] == 'c' && data[start + 1] == 'y')
		parse_cylinder(minirt, data, i, idx);
	else if (data[start] == 'c' && data[start + 1] == 'u')
		parse_cube(minirt, data, i, idx);
	else if (data[start] == 'c' && data[start + 1] == 'o')
		parse_cone(minirt, data, i, idx);
	else
		errors(ER_OBJ_TYPE, minirt);
}
=======
	if (BONUS)
		parse_bonus(minirt, data, i, idx);
}
>>>>>>> fac9762a1543c7c015675c63cef213e9d71331ec:src/parsing/322parse_objects.c
