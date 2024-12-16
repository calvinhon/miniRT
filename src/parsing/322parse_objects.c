/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   322parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honguyen <honguyen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:32:20 by honguyen          #+#    #+#             */
/*   Updated: 2024/12/16 20:22:17 by honguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"


void	*allocate_obj(t_minirt *minirt, t_objtype type)
{
	size_t	obj_index;

	obj_index = minirt->scene.n_objs++;
	minirt->scene.objects[obj_index].type = PLANE;
	minirt->scene.objects[obj_index].data = malloc(sizeof(t_plane));
	if (!minirt->scene.objects[obj_index].data)
		errors(ER_MEMORY_ALLOCATION, minirt);
	return (minirt->scene.objects[obj_index].data);
}


void	parse_plane(t_minirt *minirt, char *data, size_t *i)
{

	t_plane	*plane;

	plane = (t_plane *)allocate_obj(minirt, PLANE);
	(*i) += 2;
	while (data[*i] == ' ' || data[*i] == '\t')
		(*i)++;
	plane->point = parse_point(data, i);
	while (data[*i] == ' ' || data[*i] == '\t')
		(*i)++;
	plane->normal = parse_vector(data, i);
	while (data[*i] == ' ' || data[*i] == '\t')
		(*i)++;
	plane->color = parse_color(data, i);
	while (data[*i] == ' ' || data[*i] == '\t')
		(*i)++;
	minirt->scene.objects[obj_index].reflection = parse_float(data, i);
	while (data[*i] == ' ' || data[*i] == '\t')
		(*i)++;
	minirt->scene.objects[obj_index].shininess = parse_float(data, i);

}


void	parse_object(t_minirt *minirt, char *data, int *i)
{
	size_t	start;

	start = *i;
	if (data[start] == 'p' && data[start + 1] == 'l')
		parse_plane(minirt, data, &i);
	else if (data[start] == 's' && data[start + 1] == 'p')
		parse_sphere(minirt, data, &i);
	else if (data[start] == 'c' && data[start + 1] == 'y')
		parse_cylinder(minirt, data, &i);
	else if (data[start] == 'c' && data[start + 1] == 'u')
		parse_cubic(minirt, data, &i);
	else if (data[start] == 'c' && data[start + 1] == 'o')
		parse_cone(minirt, data, &i);
	else
		errors(ER_INVALID_OBJECT, minirt);
}

