/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:10:47 by dogs              #+#    #+#             */
/*   Updated: 2026/02/03 12:04:30 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compute_wall_dist(t_game *g)
{
	if (g->ray.side == 0)
		g->ray.perp_wall_dist = g->ray.side_dist_x - g->ray.delta_dist_x;
	else
		g->ray.perp_wall_dist = g->ray.side_dist_y - g->ray.delta_dist_y;
	g->ray.draw_door = g->ray.door_is_hit_tile;
}
