/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refractions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:56:58 by chon              #+#    #+#             */
/*   Updated: 2025/02/05 09:56:58 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	refracted_color(t_scene *s, t_comps *c, int remaining)
{
	t_refract	r;
	t_vec4d		direction;
	t_ray		ray;
	t_color		color;

	if (!c->obj->material.transparency || !remaining)
		return (create_color(0, 0, 0));
	r.n_ratio = c->n1 / c->n2;
	r.cos_i = dot_pointers(&c->eye_v, &c->normal_v);
	r.sin2_t = pow(r.n_ratio, 2) * (1 - pow(r.cos_i, 2));
	if (r.sin2_t > 1)
		return (create_color(0, 0, 0));
	r.cos_t = sqrt(1 - r.sin2_t);
	direction = subtract_vectors_val(\
		scale_vector_re(&c->normal_v, r.n_ratio * r.cos_i - r.cos_t), \
		scale_vector_re(&c->eye_v, r.n_ratio));
	ray = create_ray(&c->under_point, &direction);
	// printf("direction: %.2f %.2f %.2f\n", direction.x, direction.y, direction.z);
	color = color_at(s, &ray, remaining - 1);
	// printf("refract: %.2f %.2f %.2f\n", color.r, color.g, color.b);
	return (scale_color(&color, c->obj->material.transparency));
}

bool	is_container(t_list **containers, t_object *o)
{
	t_list	*node;
	t_list	*prev;

	node = *containers;
	prev = NULL;
	while (node)
	{
		if (node->content == o)
		{
			if (prev)
				prev->next = node->next;
			else
				*containers = node->next;
			ft_lstdelone(node, NULL);
			return (1);
		}
		prev = node;
		node = node->next;
	}
	return (0);
}

bool	is_ordered(t_itx_grp *xs)
{
	int		i;
	t_itx	temp_itx;

	i = -1;
	while (++i < xs->count - 1)
	{
		if (xs->arr[i].t > xs->arr[i + 1].t)
		{
			temp_itx = xs->arr[i];
			xs->arr[i] = xs->arr[i + 1];
			xs->arr[i + 1] = temp_itx;
			return (0);
		}
	}
	return (1);
}

void	sort_xs(t_itx_grp *xs, t_itx **itx)
{
	int			i;
	t_itx		temp_itx;
	t_object	*temp_obj;

	i = -1;
	temp_obj = (*itx)->obj;
	while (!is_ordered(xs))
	{
		while (++i < xs->count - 1)
		{
			if (xs->arr[i].t > xs->arr[i + 1].t)
			{
				temp_itx = xs->arr[i];
				xs->arr[i] = xs->arr[i + 1];
				xs->arr[i + 1] = temp_itx;
			}
		}
		i = -1;
	}
	i = -1;
	while (++i < xs->count)
		if (xs->arr[i].obj == temp_obj)
			*itx = &xs->arr[i];
}

void	prepare_refractions(t_itx_grp *xs, t_itx **itx)
{
	int		i;
	t_list	*s;

	sort_xs(xs, itx);
	s = NULL;
	i = -1;
	while (++i < xs->count)
	{
		xs->arr[i].n1 = 1;
		xs->arr[i].n2 = 1;
		if (xs->arr[i].obj->material.refractive)
		{
			if (s)
				xs->arr[i].n1 = ((t_object *)(ft_lstlast(s)->content)) \
					->material.refractive;
			if (!s || !is_container(&s, xs->arr[i].obj))
				ft_lstadd_back(&s, ft_lstnew(xs->arr[i].obj));
			if (s)
				xs->arr[i].n2 = ((t_object *)(ft_lstlast(s)->content)) \
					->material.refractive;
			if (xs->arr[i].obj->type == PLANE && ft_lstsize(s) == 1)
				ft_lstclear(&s, NULL);
		}
	}
}
