/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:02:27 by jmateo-v          #+#    #+#             */
/*   Updated: 2026/02/04 16:52:28 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square(t_game *g, int x, int y, int color)
{
	int	py;
	int	px;

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

static void	draw_small_square(t_game *g, int x, int y, int color)
{
	int	py;
	int	px;

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

static void	draw_player(t_game *g)
{
	int	px;
	int	py;

	px = g->player.x * MM_SCALE;
	py = g->player.y * MM_SCALE;
	draw_small_square(g, px - 2, py - 2, PLAYER_COLOR);
}

static void	handle_tile(t_game *g, int x, int y)
{
	char	c;
	int		px;
	int		py;

	c = g->map.grid[y][x];
	px = x * MM_SCALE;
	py = y * MM_SCALE;
	if (c == '1')
		draw_square(g, px, py, MM_WALL);
	else if (c == ' ')
		return ;
	else if (c == 'D')
		draw_square(g, px, py, MM_DOOR);
	else
	{
		draw_square(g, px, py, MM_FLOOR);
		if (c == 'X')
			draw_small_square(g, px, py, MM_ENEMY);
	}
}

void	draw_minimap(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->map.height && g->map.grid[y])
	{
		x = 0;
		while (x < g->map.width && g->map.grid[y][x])
		{
			handle_tile(g, x, y);
			x++;
		}
		y++;
	}
	draw_player(g);
}
