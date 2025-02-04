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

bool	is_container(t_list *containers, t_object *o)
{
	t_list	*head;
	t_list	*tmp;

	head = containers;
	while (containers)
	{
		if (&((t_object *)containers->content)->type == &o->type)
		{
			while (head->next && &((t_object *)(head->next->content))->type != &o->type)
				head = head->next;
			if (head->next && head->next->next)
			{
				tmp = head->next->next;
				ft_lstdelone(head->next, NULL);
				head->next = tmp;
			}
			else
			{
				ft_lstdelone(head->next, NULL);
				head->next = NULL;
			}
			return (1);
		}
		containers = containers->next;
	}
	return (0);
}

void	prepare_refractions(t_itx *itx, t_comps *comps, t_itx_grp *xs)
{
	int		i;
	t_list	*containers;

	(void)itx;
	(void)comps;
	i = -1;
	while (!is_ordered(xs))
	{
		while (++i < xs->count - 1)
			if (xs->arr[i].t > xs->arr[i + 1].t)
				swap_itx(&xs->arr[i], &xs->arr[i + 1]);
		i = -1;
	}
	containers = NULL;
	i = -1;
	while (++i < xs->count)
	{
		if (xs->arr[i].obj->material.refractive)
		{
			printf("i: %d\n", i);
			if (!containers)
				xs->arr[i].n1 = 1;
			else
				xs->arr[i].n1 = ((t_object *)(ft_lstlast(containers)->content))->material.refractive;
			if (!containers || !is_container(containers, xs->arr[i].obj))
				ft_lstadd_back(&containers, ft_lstnew(xs->arr[i].obj));
		}
	}
	printf("list length: %d\n", ft_lstsize(containers));
	ft_lstclear(&containers, NULL);
}