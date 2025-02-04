#include "minirt.h"

bool	is_ordered(t_itx_grp *xs)
{
	int	i;

	i = -1;
	while (++i < xs->count - 1)
		if (xs->arr[i].t > xs->arr[i + 1].t)
			return (0);
	return (1);
}

void	swap_itx(t_itx *itx_a, t_itx *itx_b)
{
	t_itx	temp_itx;

	temp_itx = *itx_a;
	*itx_a = *itx_b;
	*itx_b = temp_itx;
}

bool	is_container(t_list **containers, t_object *o)
{
	t_list	*node;
	t_list	*tmp;

	node = *containers;
	tmp = node;
	if (&((t_object *)node->content)->type == &o->type)
	{
		ft_lstdelone(node, NULL);
		*containers = NULL;
		return (1);
	}
	while (node)
	{
		if (node->next && &((t_object *)node->next->content)->type == &o->type)
		{
			if (node->next->next)
			{
				tmp = node->next->next;
				ft_lstdelone(node->next, NULL);
				node->next = tmp;
			}
			else if (node->next)
			{
				ft_lstdelone(node->next, NULL);
				node->next = NULL;
			}
			return (1);
		}
		node = node->next;
	}
	return (0);
}

void	sort_xs(t_itx_grp *xs)
{
	int	i;

	i = -1;
	while (!is_ordered(xs))
	{
		while (++i < xs->count - 1)
			if (xs->arr[i].t > xs->arr[i + 1].t)
				swap_itx(&xs->arr[i], &xs->arr[i + 1]);
		i = -1;
	}
}

void	prepare_refractions(t_itx *itx, t_comps *comps, t_itx_grp *xs)
{
	int		i;
	t_list	*containers;

	(void)itx;
	(void)comps;
	sort_xs(xs);
	containers = NULL;
	i = -1;
	while (++i < xs->count)
	{
		if (xs->arr[i].obj->material.refractive)
		{
			if (!containers)
				xs->arr[i].n1 = 1;
			else
				xs->arr[i].n1 =
					((t_object *)(ft_lstlast(containers)->content))->material.refractive;
			if (!containers || !is_container(&containers, xs->arr[i].obj))
				ft_lstadd_back(&containers, ft_lstnew(xs->arr[i].obj));
			if (!containers)
				xs->arr[i].n2 = 1;
			else
				xs->arr[i].n2 =
					((t_object *)(ft_lstlast(containers)->content))->material.refractive;
		}
	}
}
