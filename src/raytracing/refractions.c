#include "minirt.h"

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
	int	i;

	i = -1;
	while (++i < xs->count - 1)
		if (xs->arr[i].t > xs->arr[i + 1].t)
			return (0);
	return (1);
}

void	sort_xs(t_itx_grp *xs)
{
	int		i;
	t_itx	temp_itx;

	i = -1;
	while (!is_ordered(xs))
	{
		while (++i < xs->count - 1)
			if (xs->arr[i].t > xs->arr[i + 1].t)
			{
				temp_itx = xs->arr[i];
				xs->arr[i] = xs->arr[i + 1];
				xs->arr[i + 1] = temp_itx;
			}
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
