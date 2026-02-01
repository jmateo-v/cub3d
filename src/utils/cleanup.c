/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 19:17:27 by dogs              #+#    #+#             */
/*   Updated: 2026/02/01 20:50:52 by adrlinei         ###   ########.fr       */
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
void destroy_anim(mlx_t *mlx, t_anim *anim)
{
    int i;
     
    i = 0;
    while (i < anim->frame_count)
    {
        if (anim->frames[i])
            mlx_delete_image(mlx, anim->frames[i]);
        i++;
    }
}
static void destroy_sprites(t_game *g)
{
    int i;

    if (!g->sprites)
        return;

    i = 0;
    while (i < g->n_sprites)
    {
        destroy_anim(g->mlx, &g->sprites[i].anim);
        i++;
    }
    free(g->sprites);
    g->sprites = NULL;
    g->n_sprites = 0;
}


void cleanup(t_game *g)
{
    destroy_textures(g);
    destroy_sprites(g);
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
     if (g->map.grid)
	free_array(g->map.grid);
}
void close_game(void *param)
{
    t_game *g = param;
    cleanup(g);
    exit(0);
}
