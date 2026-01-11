/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_step_and_side.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:42:46 by dogs              #+#    #+#             */
/*   Updated: 2026/01/08 18:56:56 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void compute_step_x(t_game *g, double pos_x)
{
    if (g->ray.dir_x < 0)
    {
        g->ray.step_x = -1;
        g->ray.side_dist_x = (pos_x - g->ray.map_x) * g->ray.delta_dist_x;
    }
    else
    {
        g->ray.step_x = 1;
        g->ray.side_dist_x = (g->ray.map_x + 1.0 - pos_x) * g->ray.delta_dist_x;
    }
}

static void compute_step_y(t_game *g, double pos_y)
{
    if (g->ray.dir_y < 0)
    {
        g->ray.step_y = -1;
        g->ray.side_dist_y = (pos_y - g->ray.map_y) * g->ray.delta_dist_y;
    }
    else
    {
        g->ray.step_y = 1;
        g->ray.side_dist_y = (g->ray.map_y + 1.0 - pos_y) * g->ray.delta_dist_y;
    }
}

void compute_step_and_side_dist(t_game *g)
{
    double pos_x;
    double pos_y;

    pos_x = g->player.x;
    pos_y = g->player.y;
    g->ray.map_x = (int)pos_x;
    g->ray.map_y = (int)pos_y;

    compute_step_x(g, pos_x);
    compute_step_y(g, pos_y);
}
