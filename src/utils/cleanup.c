/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 19:17:27 by dogs              #+#    #+#             */
/*   Updated: 2026/01/19 13:59:12 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
static void destroy_textures(t_game *g)
{
    if (g->tex_n)
        mlx_delete_texture(g->tex_n);
    if (g->tex_s)
        mlx_delete_texture(g->tex_s);
    if (g->tex_w)
        mlx_delete_texture(g->tex_w);
    if (g->tex_e)
        mlx_delete_texture(g->tex_e);
    if (g->tex_d)
        mlx_delete_texture(g->tex_d);
}
void cleanup(t_game *g)
{
    destroy_textures(g);
    if (g->doors)
    {
        free(g->doors);
        g->doors = NULL;
        g->doors = 0;
    }
    if(g->frame)
        mlx_delete_image(g->mlx, g->frame);
    if (g->minimap)
        mlx_delete_image(g->mlx, g->minimap);
    if(g->mlx)
        mlx_terminate(g->mlx);
}
void close_game(void *param)
{
    t_game *g = param;
    cleanup(g);
    exit(0);
}