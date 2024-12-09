/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:52:37 by marvin            #+#    #+#             */
/*   Updated: 2024/12/11 16:52:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_minirt *parse(char *file)
{
    t_minirt    *minirt;
    char        *data;

    data = read_file(file);
    check_data(data);
    parse_data(minirt, data);
    free(data);
    return (minirt);
}
