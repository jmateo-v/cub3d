/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:53:11 by jmateo-v          #+#    #+#             */
/*   Updated: 2026/01/14 15:40:22 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_map(t_map *m)
{
    static char *hardcoded_grid[] = {
        "1111111111",
        "1000000001",
        "1010000101",
        "1010000101",
        "1000000001",
        "1000000001",
        "1010000101",
        "1001DD1001",
        "1000000001",
        "1111111111",
        NULL
    };

    m->grid = hardcoded_grid;

    m->height = 0;
    while (hardcoded_grid[m->height])
        m->height++;

    m->width = ft_strlen(hardcoded_grid[0]);

    m->floor_color = 0xFF0000FF;
    m->ceiling_color = 0xFFFFFFFF;

    m->tex_n = "textures/placeholder.png";
    m->tex_s = "textures/placeholder_S.png";
    m->tex_w = "textures/placeholder_W.png";
    m->tex_e = "textures/placeholder_E.png";
}