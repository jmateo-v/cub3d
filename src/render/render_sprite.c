/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:20:48 by dogs              #+#    #+#             */
/*   Updated: 2026/01/31 15:53:22 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void hide_frames(t_sprctx *c)
{
    int i;

    i = 0;
    while (i < c->a->frame_count)
    {
        c->a->frames[i]->instances[0].enabled = false;
        i++;
    }
}
static void sprite_transform(t_game *g, t_sprctx *c)
{
    double  sx;
    double  sy;
    double  inv;

    sx = c->s->x + 0.5 - g->player.x;
    sy = c->s->y + 0.5 - g->player.y;
    inv = g->player.plane_x * g->player.dir_y
        - g->player.dir_x * g->player.plane_y;
    inv = 1.0 / inv;
    c->tx = inv * (g->player.dir_y * sx - g->player.dir_x * sy);
    c->ty = inv * (-g->player.plane_y * sx + g->player.plane_x * sy);
}
static void sprite_screen_pos(t_sprctx *c)
{
    int screen_x;

    screen_x = WIDTH / 2;
    screen_x = screen_x * (1 + c->tx / c->ty);
    c->dx = screen_x - c->img->width / 2;
    c->dy = HEIGHT / 2 - c->img->height / 2;
}
void    render_sprites(t_game *g)
{
    t_sprctx    c;

    c.i = 0;
    while (c.i < g->n_sprites)
    {
        c.s = &g->sprites[c.i];
        c.a = &c.s->anim;
        hide_frames(&c);
        sprite_transform(g, &c);
        if (c.ty > 0)
        {
            c.img = c.a->frames[c.a->current];
            sprite_screen_pos(&c);
            c.img->instances[0].x = c.dx;
            c.img->instances[0].y = c.dy;
            c.img->instances[0].enabled = true;
        }
        c.i++;
    }
}






