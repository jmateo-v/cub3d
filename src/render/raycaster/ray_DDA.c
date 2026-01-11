/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_DDA.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:59:09 by dogs              #+#    #+#             */
/*   Updated: 2026/01/10 20:47:13 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void run_dda(t_game *g)
{
    g->ray.hit = false;
    while (g->ray.hit == false)
    {
        if (g->ray.side_dist_x < g->ray.side_dist_y)
        {
            g->ray.side_dist_x += g->ray.delta_dist_x;
            g->ray.map_x += g->ray.step_x;
            g->ray.side = 0;
        }
        else
        {
            g->ray.side_dist_y += g->ray.delta_dist_y;
            g->ray.map_y += g->ray.step_y;
            g->ray.side = 1;
        }
        if (g->ray.map_x < 0 || g->ray.map_x >= g->map.width
            || g->ray.map_y < 0 || g->ray.map_y >= g->map.height)
        {
            g->ray.hit = true;
            break;
        }
        if (g->map.grid[g->ray.map_y][g->ray.map_x] == '1')
            g->ray.hit = true;
    }
}
