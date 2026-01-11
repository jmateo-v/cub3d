/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:10:47 by dogs              #+#    #+#             */
/*   Updated: 2026/01/10 20:27:08 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void compute_wall_dist(t_game *g)
{
    if (g->ray.side == 0)
    {
        g->ray.perp_wall_dist =
            (g->ray.map_x - g->player.x + (1 - g->ray.step_x) / 2)
            / g->ray.dir_x;
    }
    else
    {
        g->ray.perp_wall_dist =
            (g->ray.map_y - g->player.y + (1 - g->ray.step_y) / 2)
            / g->ray.dir_y;
    }
}