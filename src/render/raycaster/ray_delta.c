/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_delta.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:29:30 by dogs              #+#    #+#             */
/*   Updated: 2026/01/08 18:32:07 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void compute_delta_dist(t_game *g)
{
    if (g->ray.dir_x == 0)
        g->ray.delta_dist_x = 1e30;
    else
        g->ray.delta_dist_x = fabs(1 / g->ray.dir_x);
    if (g->ray.dir_y == 0)
        g->ray.delta_dist_y = 1e30;
    else
        g->ray.delta_dist_y = fabs(1 / g->ray.dir_y);
}