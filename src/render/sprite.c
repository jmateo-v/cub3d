/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:13:31 by dogs              #+#    #+#             */
/*   Updated: 2026/01/31 15:16:05 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void update_anim(t_anim *anim)
{
    anim->timer++;

    if (anim->timer >= 8)
    {
        anim->current = (anim->current + 1) % anim->frame_count;
        anim->timer = 0;
    }
}
void anim_sprites(t_game *g)
{
    int i;
    i = 0;

    while(i < g->n_sprites)
    {
        update_anim(&g->sprites[i].anim);
        i++;
    }
}