/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:02:27 by jmateo-v          #+#    #+#             */
/*   Updated: 2026/01/14 14:54:23 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void draw_square(t_game *g, int x, int y, int color)
{
	int py;
	int px;

	py = 0;
	while (py < MM_SCALE)
	{
		px = 0;
		while (px < MM_SCALE)
		{
			mlx_put_pixel(g->minimap, x + px, y + py, color);
			px++;
		}
		py++;
	}
}
static void draw_small_square(t_game *g, int x, int y, int color)
{
	int py;
	int px;

	py = 0;
	while (py < MM_SCALE - 6)
	{
		px = 0;
		while (px < MM_SCALE - 6)
		{
			mlx_put_pixel(g->minimap, x + px, y + py, color);
			px++;
		}
		py++;
	}
}
static void draw_player(t_game *g)
{
	int px;
	int py;

	px = g->player.x * MM_SCALE;
	py = g->player.y * MM_SCALE;
	draw_small_square(g, px - 2 ,py - 2, PLAYER_COLOR);
}
void	draw_minimap(t_game *g)
{
	int x;
	int y;

	y = 0;
	while(y < g->map.height)
	{
		x = 0;
		while(x < g->map.width)
		{
			if (g->map.grid[y][x] == '1')
				draw_square(g, x * MM_SCALE, y * MM_SCALE, MM_WALL);
			else
				draw_square(g, x * MM_SCALE, y * MM_SCALE, MM_FLOOR);
			x++;
		}
		y++;
	}
	draw_player(g);
}
