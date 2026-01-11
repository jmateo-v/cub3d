/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:16:11 by dogs              #+#    #+#             */
/*   Updated: 2026/01/08 18:23:24 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void compute_ray_dir(t_game *g, int x)
{
    double camera_x;

    camera_x = 2 * x / (double)WIDTH - 1;
    g->ray.dir_x = g->player.dir_x + g->player.plane_x * camera_x;
    g->ray.dir_y = g->player.dir_y + g->player.plane_y * camera_x;
}