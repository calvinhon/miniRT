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
	itx_a = itx_b;
	itx_b = *temp_itx;
}

int	obj_itx_count(t_itx_grp *xs, t_object *o, int itx_num)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < itx_num)
	{
		if (xs->arr[i].obj == o)
			count++;
	}
	return (count);
}

void	prepare_refractions(t_itx *itx, t_comps *comps, t_itx_grp *xs)
{
	t_itx_grp	ordered_xs;
	t_itx		temp_itx;
	int			i;

	i = -1;
	while (!is_ordered(xs))
	{
		while (++i < xs->count - 1)
			if (xs->arr[i].t > xs->arr[i + 1].t)
				swap_itx(&xs->arr[i], &xs->arr[i + 1])
		i = -1;
	}
	i = -1;
	while (++i < xs->count)
	{
		while (xs->arr[i].obj->type == PLANE)
			i++;
		if (!i)
			xs->arr[i].n1 = 1;
		if (xs->arr[i].obj->material.refractive && )
			xs->arr[i].n2 = xs->arr[i].obj->material.refractive;

	}
}