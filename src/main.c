#include "minirt.h"

int main(int ac, char **av)
{
	t_mlx_vars	env;

	if (ac != 1) // change to 2
	{
		printf("Input scenes/<filename>.rt as 2nd argument"\n)
		return (1);
	}
	env.mlx = mlx_init();
	if (!env.mlx)
	{
		printf("Error initializing mlx\n");
		return (1);
	}
	return (0);
}