/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:03:35 by jmateo-v          #+#    #+#             */
/*   Updated: 2026/01/14 15:41:56 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int count_doors(t_game *g)
{
	int x;
	int y;
	int count;

	count = 0;
	y = 0;
	while(y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			if (g->map.grid[y][x] == 'D')
				++count;
			x++;
		}
		y++;
	}
	return (count);
}
static void fill_doors(t_game *g)
{
	int x;
	int y;
	
	y = 0;
	while(y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			if (g->map.grid[y][x] == 'D')
			{
				g->doors[g->n_doors].x = x;
				g->doors[g->n_doors].y = y;
				g->doors[g->n_doors].open = false;
				g->doors[g->n_doors].prog = 0.0f;
				g->doors[g->n_doors].speed = DOOR_SPEED;
				++g->n_doors;
			}
			x++;
		}
		y++;
	}
}
void init_doors(t_game *g)
{
	int count;

	count = count_doors(g);
	if (count == 0)
	{
		g->doors = NULL;
		g->n_doors = 0;
		return ;
	}
	g->doors = malloc(sizeof *g->doors * count);
	if (!g->doors)
		error_exit(ERR_DOOR_MALLOC);
	g->n_doors = 0;
	fill_doors(g);
}
