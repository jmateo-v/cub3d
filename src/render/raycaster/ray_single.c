/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:11:39 by dogs              #+#    #+#             */
/*   Updated: 2026/01/08 19:38:42 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cast_single_ray(t_game *g, int x)
{
    compute_ray_dir(g, x);
    compute_delta_dist(g);
    compute_step_and_side_dist(g);
    run_dda(g);
    compute_wall_dist(g);
    draw_wall_slice(g, x);
}