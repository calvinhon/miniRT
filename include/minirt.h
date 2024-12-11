/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chon <chon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:54:48 by chon              #+#    #+#             */
/*   Updated: 2024/12/11 15:54:48 by chon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libs/libft/libft.h"
# include "../libs/mlx_linux/mlx.h"
# include "../libs/mlx_macos/mlx.h"

# define WINDOW_W 1920
# define WINDOW_L 1080

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

void	set_controls(t_mlx_vars *env);

#endif