/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 14:51:10 by dogs              #+#    #+#             */
/*   Updated: 2026/02/03 11:14:28 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_sprites(t_game *g)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < g->map.height && g->map.grid[y])
	{
		x = 0;
		while (x < g->map.width && g->map.grid[y][x])
		{
			if (g->map.grid[y][x] == 'X')
				++count;
			x++;
		}
		y++;
	}
	return (count);
}

static void	fill_sprites(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->map.height && g->map.grid[y])
	{
		x = 0;
		while (x < g->map.width && g->map.grid[y][x])
		{
			if (g->map.grid[y][x] == 'X')
			{
				g->sprites[g->n_sprites].x = x;
				g->sprites[g->n_sprites].y = y;
				init_anim(&g->sprites[g->n_sprites].anim);
				++g->n_sprites;
			}
			x++;
		}
		y++;
	}
}

void	init_sprites(t_game *g)
{
	int	count;

	count = count_sprites(g);
	if (count == 0)
	{
		g->sprites = NULL;
		g->n_sprites = 0;
		return ;
	}
	g->sprites = malloc(sizeof * g->sprites * count);
	if (!g->sprites)
		error_exit(ERR_SPRITE_MALLOC);
	g->n_sprites = 0;
	fill_sprites(g);
}
