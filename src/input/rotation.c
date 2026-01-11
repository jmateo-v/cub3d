/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:39:47 by dogs              #+#    #+#             */
/*   Updated: 2026/01/10 19:52:04 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void rotate_left(t_game *g)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = g->player.dir_x;
    old_plane_x = g->player.plane_x;
    g->player.dir_x = g->player.dir_x * cos(ROTATE_SPEED)
        - g->player.dir_y * sin(ROTATE_SPEED);
    g->player.dir_y = old_dir_x * sin(ROTATE_SPEED)
        + g->player.dir_y * cos(ROTATE_SPEED);
    g->player.plane_x = g->player.plane_x * cos(ROTATE_SPEED)
        - g->player.plane_y * sin(ROTATE_SPEED);
    g->player.plane_y = old_plane_x * sin(ROTATE_SPEED)
        + g->player.plane_y * cos(ROTATE_SPEED);
}
void rotate_right(t_game *g)
{
    double old_dir_x;
    double old_plane_x;

    old_dir_x = g->player.dir_x;
    old_plane_x = g->player.plane_x;
    g->player.dir_x = g->player.dir_x * cos(-ROTATE_SPEED)
        - g->player.dir_y * sin(-ROTATE_SPEED);
    g->player.dir_y = old_dir_x * sin(-ROTATE_SPEED)
        + g->player.dir_y * cos(-ROTATE_SPEED);
    g->player.plane_x = g->player.plane_x * cos(-ROTATE_SPEED)
        - g->player.plane_y * sin(-ROTATE_SPEED);
    g->player.plane_y = old_plane_x * sin(-ROTATE_SPEED)
        + g->player.plane_y * cos(-ROTATE_SPEED);
}
