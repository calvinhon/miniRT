#ifndef MINIRT_H
# define MINIRT_H

# include "../libs/libft/libft.h"
# include "../libs/mlx_linux/mlx.h"
# include "../libs/mlx_macos/mlx.h"

typedef struct s_mlx_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		l_len;
	int		end;
}	t_mlx_vars;

typedef struct s_world
{
	t_mlx_vars	mlx;
}	t_world;

#endif