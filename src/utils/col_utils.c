/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 20:01:20 by dogs              #+#    #+#             */
/*   Updated: 2026/01/12 15:00:56 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool is_bounded(t_game *g, int x, int y)
{
    if (y < 0 || y >= g->map.height)
        return (0);
    if (x < 0 || x >= g->map.width)
        return(0);
    return (1);
}
bool is_wall(t_game *g, double x, double y)
{
    int mx;
    int my;

    mx = (int)x;
    my = (int)y;
    if (mx < 0 || my < 0 || my >= g->map.height || mx >= g->map.width)
        return 1;
    return(g->map.grid[my][mx] == '1');
}