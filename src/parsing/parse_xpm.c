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

#include "miniRT.h"
#include "macros.h"
// #include "libft.h"
#include "colors.h"

static bool	parse_new_bump_xpm(t_material *obj_mat, t_minirt *minirt, char *filename)
{
	t_list	*new;

	new = ft_lstnew(NULL);
	new->content = malloc(sizeof(t_tex_frame));
	if (!new->content)
		return (free(new), minirt->error_code = 3, false);
	((t_tex_frame *)new->content)->name = ft_strdup(filename);
	if (!((t_tex_frame *)new->content)->name)
		return (ft_lstdelone(new, free), minirt->error_code = 3, false);

	((t_tex_frame *)new->content)->fra_tex = rt_xpm_file_to_canvas(
			filename, minirt->mlx);
	//test	
	//printf("export xpm to canvas\n");
	obj_mat->fra_tex = ((t_tex_frame *)new->content)->fra_tex;
	if (!obj_mat->fra_tex)
		return (free(((t_tex_frame *)new->content)->name), ft_lstdelone(new,
				free), minirt->error_code = 3, false);
	ft_lstadd_back(&minirt->textures, new);
	return (true);
}
bool parse_bump_xpm(t_material *material, char *data, size_t *i, t_minirt *minirt)
{
    t_list *temp;
    size_t len;
    char filename[256];
  
  	while (data[*i] == '\t' || data[*i] == ' ' || data[*i] == '\n')
		(*i)++;
	len = 0;
	while (data[*i + len] != '\n' && data[*i + len] != '\0' && data[*i + len] != ' ')
    {
		filename[len] = data[*i + len];
		len++;
	}
	*i += len;
	filename[len] = '\0';

    if (len < 5 || ft_strncmp(data + len - 4, ".xpm", 4))
        return (minirt->error_code = 3, false);
    temp = minirt->textures;
    while (temp)
    {
        if (!ft_strncmp(((t_tex_frame *)temp->content)->name, filename, len))
            return (material->fra_tex = ((t_tex_frame *)temp->content)->fra_tex, true);
        if (!temp->next)
            break;
        temp = temp->next;
    }
    return (parse_new_bump_xpm(material, minirt, filename));
}
