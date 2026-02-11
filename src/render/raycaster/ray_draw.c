/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:19:25 by dogs              #+#    #+#             */
/*   Updated: 2026/02/11 15:34:46 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_tex_pixel(t_game *g, mlx_texture_t *tex, int x, t_slice *s)
{
	uint8_t		*p;
	uint32_t	color;

	p = tex->pixels + (s->tex_y * tex->width + s->tex_x) * 4;
	color = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
	mlx_put_pixel(g->frame, x, s->start, color);
}

static mlx_texture_t	*get_tex(t_game *g)
{
	if (g->ray.draw_door)
		return (g->tex_d);
	if (g->ray.side == 0)
	{
		if (g->ray.step_x > 0)
			return (g->tex_e);
		return (g->tex_w);
	}
	if (g->ray.step_y > 0)
		return (g->tex_s);
	return (g->tex_n);
}

static int	get_tex_x(t_game *g, mlx_texture_t *tex)
{
	double	wall_x;
	int		tex_x;

	if (g->ray.side == 0)
		wall_x = g->player.y + g->ray.perp_wall_dist * g->ray.dir_y;
	else
		wall_x = g->player.x + g->ray.perp_wall_dist * g->ray.dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (g->ray.side == 0 && g->ray.dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (g->ray.side == 1 && g->ray.dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_tex_column(t_game *g, mlx_texture_t *tex, int x, t_slice *s)
{
	double	step;
	double	tex_pos;

	step = (double)tex->height / s->line_h;
	tex_pos = (s->start - HEIGHT / 2 + s->line_h / 2) * step;
	while (s->start <= s->end)
	{
		s->tex_y = (int)tex_pos;
		if (s->tex_y < 0)
			s->tex_y = 0;
		if (s->tex_y >= (int)tex->height)
			s->tex_y = tex->height - 1;
		tex_pos += step;
		put_tex_pixel(g, tex, x, s);
		s->start++;
	}
}

void	draw_wall_slice(t_game *g, int x)
{
	int				line_h;
	int				start;
	int				end;
	mlx_texture_t	*tex;
	t_slice			s;

	line_h = (int)(HEIGHT / g->ray.perp_wall_dist);
	start = -line_h / 2 + HEIGHT / 2;
	if (start < 0)
		start = 0;
	end = line_h / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	tex = get_tex(g);
	s.tex_x = get_tex_x(g, tex);
	if (g->ray.draw_door)
	{
		start += (int)(line_h * g->doors[g->ray.door_index].prog);
		if (start > end)
			return ;
	}
	s.start = start;
	s.end = end;
	s.line_h = line_h;
	draw_tex_column(g, tex, x, &s);
}
