/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_DDA.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:59:09 by dogs              #+#    #+#             */
/*   Updated: 2026/01/19 20:00:31 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool is_out_of_bounds(t_game *g, int x, int y)
{
    return (x < 0 || x >= g->map.width || y < 0 || y >= g->map.height);
}

static void step_ray(t_ray *ray)
{
    if (ray->side_dist_x < ray->side_dist_y)
    {
        ray->side_dist_x += ray->delta_dist_x;
        ray->map_x += ray->step_x;
        ray->side = 0;
    }
    else
    {
        ray->side_dist_y += ray->delta_dist_y;
        ray->map_y += ray->step_y;
        ray->side = 1;
    }
}

static bool handle_wall_hit(t_game *g)
{
    if (g->map.grid[g->ray.map_y][g->ray.map_x] == '1')
    {
        g->ray.hit = true;
        return true;
    }
    return false;
}

static bool handle_door_hit(t_game *g)
{
    int idx;
    t_door *d;

    if (g->map.grid[g->ray.map_y][g->ray.map_x] != 'D')
        return false;
    idx = find_door_index(g, g->ray.map_x, g->ray.map_y);
    d = &g->doors[idx];
    g->ray.hit_door = true;
    g->ray.door_index = idx;
    if (d->prog < 1.0f)
    {
        g->ray.hit = true;
        g->ray.door_is_hit_tile = true;
        return true;
    }
    return false;
}

void run_dda(t_game *g)
{
    g->ray.hit = false;
    g->ray.hit_door = false;
    g->ray.door_index = -1;
    g->ray.door_is_hit_tile = false;

    while (!g->ray.hit)
    {
        step_ray(&g->ray);
        if (is_out_of_bounds(g, g->ray.map_x, g->ray.map_y))
        {
            g->ray.hit = true;
            break;
        }
        if (handle_wall_hit(g))
            break;

        if (handle_door_hit(g))
            break;
    }
}




