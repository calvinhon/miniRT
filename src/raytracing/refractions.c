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

int	obj_itx_count(t_itx_grp *xs, t_object *o, int itx_num)
{
	int	i;
	int	count;

	if (!itx_num)
		return (1);
	i = -1;
	count = 0;
	while (++i < itx_num)
	{
		if (xs->arr[i].obj == o)
			count++;
	}
	return (count);
}

bool	is_container(t_list *containers, t_object *o)
{
	t_list	*head;
	t_list	*tmp;

	while (containers)
	{
		head = containers;
		if (&((t_itx *)containers->content)->obj == &o)
		{
			while (head->next && &((t_itx *)(head->next->content))->obj != &o)
				head = head->next;
			tmp = head->next->next;
			ft_lstdelone(head->next, NULL);
			head->next = tmp;
			printf("hits\n");
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
			if (!containers)
				xs->arr[i].n1 = 1;
			else
				xs->arr[i].n1 = ((t_object *)(ft_lstlast(containers)->content))->material.refractive;
			if (!is_container(containers, xs->arr[i].obj))
				ft_lstadd_back(&containers, ft_lstnew(&xs->arr[i].obj));
		}
	}
	printf("%d\n", ft_lstsize(containers));
	ft_lstclear(&containers, NULL);
	// while (++i < xs->count - 1)
	// {
	// 	if (xs->arr[i].obj->material.refractive)
	// 	{
	// 		if (!i)
	// 		{
	// 			xs->arr[i].n1 = 1;
	// 			xs->arr[i].n2 = xs->arr[i].obj->material.refractive;
	// 		}
	// 		else
	// 		{
	// 			xs->arr[i].n1 = xs->arr[i - 1].obj->material.refractive;
	// 			if (!(obj_itx_count(xs, xs->arr[i].obj, i) % 2))
	// 				xs->arr[i].n2 = xs->arr[i].obj->material.refractive;
	// 			else
	// 			{
	// 				xs->arr[i].n1 = xs->arr[i].obj->material.refractive;
	// 				xs->arr[i].n2 = xs->arr[i + 1].obj->material.refractive;
	// 			}
	// 		}
	// 	}
	// }
	// if (xs->arr[i].obj->material.refractive)
	// {
	// 	xs->arr[i].n1 = xs->arr[i].obj->material.refractive;
	// 	xs->arr[i].n2 = 1;
	// }
}