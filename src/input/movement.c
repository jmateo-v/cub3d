/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:08:18 by dogs              #+#    #+#             */
/*   Updated: 2026/01/12 14:52:50 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_foward(t_game *g)
{
    double new_x;
    double new_y;

    new_x = g->player.x + g->player.dir_x * MOVE_SPEED;
    new_y = g->player.y + g->player.dir_y * MOVE_SPEED;
    if (is_bounded(g, (int)new_x, (int)g->player.y)
        && !is_wall(g, new_x + g->player.dir_x * PADDING, g->player.y))
        g->player.x = new_x;
    if (is_bounded(g, (int)g->player.x, (int)new_y)
        && !is_wall(g, g->player.x, new_y + g->player.dir_y * PADDING))
        g->player.y = new_y;
}
void move_backwards(t_game *g)
{
    double new_x;
    double new_y;

    new_x = g->player.x - g->player.dir_x * MOVE_SPEED;
    new_y = g->player.y - g->player.dir_y * MOVE_SPEED;
    if (is_bounded(g, (int)new_x, (int)g->player.y)
        && !is_wall(g, new_x - g->player.dir_x * PADDING, g->player.y))
        g->player.x = new_x;
    if (is_bounded(g, (int)g->player.x, (int)new_y)
        && !is_wall(g, g->player.x, new_y - g->player.dir_y * PADDING))
        g->player.y = new_y;
}
void move_left(t_game *g)
{
    double new_x;
    double new_y;

    new_x = g->player.x - g->player.plane_x * MOVE_SPEED;
    new_y = g->player.y - g->player.plane_y * MOVE_SPEED;
    if (is_bounded(g, (int)new_x, (int)g->player.y)
        && !is_wall(g, new_x - g->player.plane_x * PADDING, g->player.y))
        g->player.x = new_x;
    if (is_bounded(g, (int)g->player.x, (int)new_y)
        && !is_wall(g, g->player.x, new_y - g->player.plane_y * PADDING))
        g->player.y = new_y;
}
void move_right(t_game *g)
{
    double new_x;
    double new_y;

    new_x = g->player.x + g->player.plane_x * MOVE_SPEED;
    new_y = g->player.y + g->player.plane_y * MOVE_SPEED;
    if (is_bounded(g, (int)new_x, (int)g->player.y)
        && !is_wall(g, new_x + g->player.plane_x * PADDING, g->player.y))
        g->player.x = new_x;
    if (is_bounded(g, (int)g->player.x, (int)new_y)
        && !is_wall(g, g->player.x, new_y + g->player.plane_y * PADDING))
        g->player.y = new_y;
}