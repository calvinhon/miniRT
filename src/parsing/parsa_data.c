/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsa_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:42:00 by marvin            #+#    #+#             */
/*   Updated: 2024/12/11 18:42:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"   
    
void    parse_data(minirt, data)
{
	int		i;
	bool	ok;
	char	**tokens;

	i = -1;
	tokens = ft_split(data, ' ');
	ok = identifying(minirt, tokens);
	nc_matrix_delete(tokens, &free);
	if (!ok)
	    error(ER_SYNTAX, minirt);
}
