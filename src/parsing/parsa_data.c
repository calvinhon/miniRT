/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsa_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:54:09 by marvin            #+#    #+#             */
/*   Updated: 2024/12/12 16:54:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void parse_data(t_minirt *minirt, char *data)
{
    char *ptr = data;
    char *end;

    while (*ptr)
    {
        // Skip whitespace
        while (*ptr == ' ' || *ptr == '\n' || *ptr == '\t')
            ptr++;

        // Find the next space or newline to extract the token
        end = ptr;
        while (*end && *end != ' ' && *end != '\n' && *end != '\t')
            end++;

        // Extract the token
        size_t token_len = end - ptr;
        char token[token_len + 1];
        ft_memcpy(token, ptr, token_len);
        token[token_len] = '\0';

        // Process the token
        if (ft_strcmp(token, "A") == 0)
        {
            t_ambient ambient;
            ptr = end;
            ambient.ratio = ft_atof(ptr);
            while (*ptr && *ptr != ' ')
                ptr++;
            ambient.color = parse_color(ptr);
            minirt->ambient = ambient;
        }
        else if (ft_strcmp(token, "L") == 0)
        {
            t_light light;
            ptr = end;
            light.position = parse_vec3(ptr);
            while (*ptr && *ptr != ' ')
                ptr++;
            light.intensity = ft_atof(ptr);
            while (*ptr && *ptr != ' ')
                ptr++;
            light.color = parse_color(ptr);
            minirt->light = light;
        }
        else if (ft_strcmp(token, "sp") == 0)
        {
            t_sphere sphere;
            ptr = end;
            sphere.center = parse_vec3(ptr);
            while (*ptr && *ptr != ' ')
                ptr++;
            sphere.radius = ft_atof(ptr);
            while (*ptr && *ptr != ' ')
                ptr++;
            sphere.color = parse_color(ptr);
            add_sphere(minirt, sphere);
        }
        else if (ft_strcmp(token, "pl") == 0)
        {
            t_plane plane;
            ptr = end;
            plane.point = parse_vec3(ptr);
            while (*ptr && *ptr != ' ')
                ptr++;
            plane.normal = parse_vec3(ptr);
            while (*ptr && *ptr != ' ')
                ptr++;
            plane.color = parse_color(ptr);
            add_plane(minirt, plane);
        }
        else if (ft_strcmp(token, "cy") == 0)
        {
            t_cylinder cylinder;
            ptr = end;
            cylinder.base = parse_vec3(ptr);
            while (*ptr && *ptr != ' ')
                ptr++;
            cylinder.axis = parse_vec3(ptr);
            while (*ptr && *ptr != ' ')
                ptr++;
            cylinder.radius = ft_atof(ptr);
            while (*ptr && *ptr != ' ')
                ptr++;
            cylinder.height = ft_atof(ptr);
            while (*ptr && *ptr != ' ')
                ptr++;
            cylinder.color = parse_color(ptr);
            add_cylinder(minirt, cylinder);
        }
        // Move to the next token
        ptr = end;
    }
}

/**
 * Parses a color string in the format "R,G,B" and returns a t_color struct.
 */
t_color parse_color(char *str)
{
    t_color color;
    color.r = ft_atoi(str);
    while (*str && *str != ',')
        str++;
    if (*str == ',')
        str++;
    color.g = ft_atoi(str);
    while (*str && *str != ',')
        str++;
    if (*str == ',')
        str++;
    color.b = ft_atoi(str);

    return color;
}

/**
 * Parses a vector string in the format "x,y,z" and returns a t_vec3 struct.
 */
t_vec3 parse_vec3(char *str)
{
    t_vec3 vec;
    vec.x = ft_atof(str);
    while (*str && *str != ',')
        str++;
    if (*str == ',')
        str++;
    vec.y = ft_atof(str);
    while (*str && *str != ',')
        str++;
    if (*str == ',')
        str++;
    vec.z = ft_atof(str);

    return vec;
}

/**
 * Adds a sphere to the scene's list of spheres.
 */
void add_sphere(t_minirt *minirt, t_sphere sphere)
{
    if (minirt->sphere_count >= minirt->sphere_capacity)
    {
        minirt->sphere_capacity *= 2;
        minirt->spheres = realloc(minirt->spheres, minirt->sphere_capacity * sizeof(t_sphere));
        if (!minirt->spheres)
            errors(ER_MALLOC("add_sphere"), minirt);
    }
    minirt->spheres[minirt->sphere_count++] = sphere;
}

/**
 * Adds a plane to the scene's list of planes.
 */
void add_plane(t_minirt *minirt, t_plane plane)
{
    if (minirt->plane_count >= minirt->plane_capacity)
    {
        minirt->plane_capacity *= 2;
        minirt->planes = realloc(minirt->planes, minirt->plane_capacity * sizeof(t_plane));
        if (!minirt->planes)
            errors(ER_MALLOC("add_plane"), minirt);
    }
    minirt->planes[minirt->plane_count++] = plane;
}

/**
 * Adds a cylinder to the scene's list of cylinders.
 */
void add_cylinder(t_minirt *minirt, t_cylinder cylinder)
{
    if (minirt->cylinder_count >= minirt->cylinder_capacity)
    {
        minirt->cylinder_capacity *= 2;
        minirt->cylinders = realloc(minirt->cylinders, minirt->cylinder_capacity * sizeof(t_cylinder));
        if (!minirt->cylinders)
            errors(ER_MALLOC("add_cylinder"), minirt);
    }
    minirt->cylinders[minirt->cylinder_count++] = cylinder;
}
