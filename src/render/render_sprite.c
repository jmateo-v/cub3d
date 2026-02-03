/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:20:48 by dogs              #+#    #+#             */
/*   Updated: 2026/02/03 11:57:41 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_single_stripe(t_game *g, t_sprctx *c, int stripe)
{
	int			y;
	int			d;
	int			tex_y;
	int			tex_x;
	uint32_t	color;

	tex_x = (int)(256 * (stripe - (-c->sprite_w / 2 + c->screen_x))
			* c->tex->width / c->sprite_w) / 256;
	y = c->draw_start_y;
	while (y < c->draw_end_y)
	{
		d = (y * 256) - (HEIGHT * 128) + (c->sprite_h * 128);
		tex_y = ((d * c->tex->height) / c->sprite_h) / 256;
		color = tex_get_pixel(c->tex, tex_x, tex_y);
		if ((color & 0xFF) != 0)
			mlx_put_pixel(g->frame, stripe, y, color);
		y++;
	}
}

static void	draw_sprite_stripes(t_game *g, t_sprctx *c)
{
	int	stripe;

	stripe = c->draw_start_x;
	while (stripe < c->draw_end_x)
	{
		if (c->ty < g->zbuffer[stripe])
			draw_single_stripe(g, c, stripe);
		stripe++;
	}
}

static void	render_single_sprite(t_game *g, t_sprctx *c)
{
	sprite_transform(g, c);
	if (c->ty <= 0)
		return ;
	sprite_screen_setup(c);
	draw_sprite_stripes(g, c);
}

void	render_sprites(t_game *g)
{
	t_sprctx	c;

	c.i = 0;
	while (c.i < g->n_sprites)
	{
		c.s = &g->sprites[c.i];
		c.a = &c.s->anim;
		c.tex = c.a->frames[c.a->current];
		render_single_sprite(g, &c);
		c.i++;
	}
}
