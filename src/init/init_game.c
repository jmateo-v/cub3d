/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:12:12 by dogs              #+#    #+#             */
/*   Updated: 2026/02/03 11:09:40 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_mlx(t_game *g)
{
	g->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!g->mlx)
		error_exit(ERR_MLX_INIT);
}

static void	init_frame(t_game *g)
{
	g->frame = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->frame)
	{
		cleanup(g);
		error_exit(ERR_FRAME_INIT);
	}
	if (mlx_image_to_window(g->mlx, g->frame, 0, 0) < 0)
	{
		cleanup(g);
		error_exit(ERR_IMG_TO_WIN);
	}
}

static void	init_minimap(t_game *g)
{
	int	mm_w;
	int	mm_h;

	mm_w = g->map.width * MM_SCALE;
	mm_h = g->map.height * MM_SCALE;
	g->minimap = mlx_new_image(g->mlx, mm_w, mm_h);
	if (!g->minimap)
	{
		cleanup(g);
		error_exit(ERR_FRAME_INIT);
	}
	if (mlx_image_to_window(g->mlx, g->minimap, 20, 20) < 0)
	{
		cleanup(g);
		error_exit(ERR_IMG_TO_WIN);
	}
}

static void	init_textures(t_game *g)
{
	g->tex_n = mlx_load_png(g->map.tex_n);
	g->tex_s = mlx_load_png(g->map.tex_s);
	g->tex_w = mlx_load_png(g->map.tex_w);
	g->tex_e = mlx_load_png(g->map.tex_e);
	g->tex_d = mlx_load_png("textures/door.png");
	if (!g->tex_n || !g->tex_s || !g->tex_w || !g->tex_e || !g->tex_d)
	{
		cleanup(g);
		error_exit(ERR_TEXTURE_INIT);
	}
}

void	init_game(t_game *g, int argc, char **argv)
{
	ft_memset(g, 0, sizeof(t_game));
	initial_parsing(g, argc, argv);
	init_map(g);
	init_mlx(g);
	init_frame(g);
	init_minimap(g);
	init_doors(g);
	init_sprites(g);
	init_textures(g);
	g->last_mouse_x = -1;
}
