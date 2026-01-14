/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:12:12 by dogs              #+#    #+#             */
/*   Updated: 2026/01/14 15:36:50 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
static void init_mlx(t_game *g)
{
    g->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
    if (!g->mlx)
        error_exit(ERR_MLX_INIT);
}
static void init_frame(t_game *g)
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
static void init_minimap(t_game *g)
{
    int mm_w;
    int mm_h;

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

static void init_player(t_game *g)
{
    //HARDCODED!!! SHOULD BE PARSED FROM .CUB
    g->player.x = 3.5;
    g->player.y = 3.5;

    g->player.dir_x = -1.0;
    g->player.dir_y = 0.0;

    g->player.plane_x = 0.0;
    g->player.plane_y = 0.66;
}
static void init_textures(t_game *g)
{
    g->tex_n = mlx_load_png(g->map.tex_n);
    g->tex_s = mlx_load_png(g->map.tex_s);
    g->tex_w = mlx_load_png(g->map.tex_w);
    g->tex_e = mlx_load_png(g->map.tex_e);
    if (!g->tex_n || !g->tex_s || !g->tex_w || !g->tex_e)
        error_exit(ERR_TEXTURE_INIT);
}
void    init_game(t_game *g)
{
    ft_memset(g, 0, sizeof(t_game));
    init_mlx(g);
    init_frame(g);
    init_map(&g->map);
    init_minimap(g);
    init_doors(g);
    init_textures(g);
    init_player(g);
}