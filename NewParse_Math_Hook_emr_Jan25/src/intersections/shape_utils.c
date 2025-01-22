/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nth <nth@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:30:03 by nth          #+#    #+#             */
/*   Updated: 2024/11/18 13:30:07 by nth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	transpose_mat4s(const t_mat4s *m, t_mat4s *out)
{
    if (m == NULL || out == NULL)
     {
         ft_printf("Error: NULL pointer passed to transpose_mat4s\n");
         return;
     }
	 int    i;
	 int	j;

	 i = 0;
	 while (i < 4)
     {
         j = 0;
         while (j < 4)
         {
             out->a[i][j] = m->a[j][i];
             j++;
         }
         i++;
     }
}
