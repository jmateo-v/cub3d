/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rs_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:44:51 by dogs              #+#    #+#             */
/*   Updated: 2026/02/03 11:59:52 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_transform(t_game *g, t_sprctx *c)
{
	double	sx;
	double	sy;
	double	inv;

	sx = c->s->x + 0.5 - g->player.x;
	sy = c->s->y + 0.5 - g->player.y;
	inv = g->player.plane_x * g->player.dir_y
		- g->player.dir_x * g->player.plane_y;
	inv = 1.0 / inv;
	c->tx = inv * (g->player.dir_y * sx - g->player.dir_x * sy);
	c->ty = inv * (-g->player.plane_y * sx + g->player.plane_x * sy);
}

void	sprite_screen_setup(t_sprctx *c)
{
	c->screen_x = (int)((WIDTH / 2.0) * (1 + c->tx / c->ty));
	c->sprite_h = abs((int)(HEIGHT / c->ty));
	c->sprite_w = abs((int)(HEIGHT / c->ty));
	c->draw_start_y = -c->sprite_h / 2 + HEIGHT / 2;
	if (c->draw_start_y < 0)
		c->draw_start_y = 0;
	c->draw_end_y = c->sprite_h / 2 + HEIGHT / 2;
	if (c->draw_end_y >= HEIGHT)
		c->draw_end_y = HEIGHT - 1;
	c->draw_start_x = -c->sprite_w / 2 + c->screen_x;
	if (c->draw_start_x < 0)
		c->draw_start_x = 0;
	c->draw_end_x = c->sprite_w / 2 + c->screen_x;
	if (c->draw_end_x >= WIDTH)
		c->draw_end_x = WIDTH - 1;
}

uint32_t	tex_get_pixel(mlx_texture_t *tex, int x, int y)
{
	uint8_t		*p;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;

	p = tex->pixels + ((y * tex->width + x) * 4);
	r = p[0];
	g = p[1];
	b = p[2];
	a = p[3];
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
