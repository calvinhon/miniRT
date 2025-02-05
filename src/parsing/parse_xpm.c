/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:55:36 by nth          #+#    #+#             */
/*   Updated: 2025/01/13 18:40:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "macros.h"
#include "colors.h"

static bool	parse_new_bump_xpm(t_material *obj_mat, t_minirt *minirt, \
	char *filename)
{
	t_list	*new;

	new = ft_lstnew(NULL);
	new->content = malloc(sizeof(t_tex_frame));
	if (!new->content)
		return (free(new), minirt->error_code = 3, false);
	((t_tex_frame *)new->content)->name = ft_strdup(filename);
	if (!((t_tex_frame *)new->content)->name)
		return (ft_lstdelone(new, free), minirt->error_code = 3, false);
	((t_tex_frame *)new->content)->bump_map = rt_xpm_file_to_canvas(\
		filename, minirt->mlx);
	obj_mat->bump_map = ((t_tex_frame *)new->content)->bump_map;
	if (!obj_mat->bump_map)
		return (free(((t_tex_frame *)new->content)->name), \
			ft_lstdelone(new, free), minirt->error_code = 3, false);
	ft_lstadd_back(&minirt->textures, new);
	return (true);
}

static bool	add_texture( t_list	*temp, const char	*filename, \
	t_material *material, size_t len)
{
	while (temp)
	{
		if (!ft_strncmp(((t_tex_frame *)temp->content)->name, \
			filename, len))
			return (material->bump_map = ((t_tex_frame *)temp->content) \
				->bump_map, true);
		if (!temp->next)
			break ;
		temp = temp->next;
	}
	return (false);
}

bool	parse_bump_xpm(t_material *material, char *data, \
	size_t *i, t_minirt *minirt)
{
	t_list	*temp;
	size_t	len;
	char	filename[256];

	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == '\n')
		(*i)++;
	len = 0;
	while (data[*i + len] != '\n' && data[*i + len] != '\0' && \
		data[*i + len] != ' ')
	{
		filename[len] = data[*i + len];
		len++;
	}
	*i += len;
	filename[len] = '\0';
	if (!fopen(filename, "r"))
		return (errors(CER_M_BUMP_FORMAT, ER_M_BUMP_FORMAT, minirt), 1);
	temp = minirt->textures;
	if (add_texture(temp, filename, material, len))
		return (true);
	return (parse_new_bump_xpm(material, minirt, filename));
}
