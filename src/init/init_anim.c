/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_anim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 14:37:25 by dogs              #+#    #+#             */
/*   Updated: 2026/01/31 15:37:05 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_image_t *init_frame(mlx_t *mlx, const char *path)
{
    mlx_texture_t *tex;
    mlx_image_t   *img;

    tex = mlx_load_png(path);
    if (!tex)
        return (NULL);
    img = mlx_texture_to_image(mlx, tex);
    mlx_delete_texture(tex);
    return (img);
}

void init_anim(mlx_t *mlx, t_anim *anim)
{
    int i;
    
    anim->frame_count = 5;
    anim->current = 0;
    anim->timer = 0;

    anim->frames[0] = init_frame(mlx, "textures/sprite/s0.png");
    anim->frames[1] = init_frame(mlx, "textures/sprite/s1.png");
    anim->frames[2] = init_frame(mlx, "textures/sprite/s2.png");
    anim->frames[3] = init_frame(mlx, "textures/sprite/s3.png");
    anim->frames[4] = init_frame(mlx, "textures/sprite/s4.png");
    i = 0;
    while( i < anim->frame_count)
    {
        mlx_image_to_window(mlx, anim->frames[i], 0, 0);
        anim->frames[i]->instances[0].enabled = false;
        i++;
    }
}
