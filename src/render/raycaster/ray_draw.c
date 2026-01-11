/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:19:25 by dogs              #+#    #+#             */
/*   Updated: 2026/01/10 22:01:53 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_wall_slice(t_game *g, int x)
{
    int line_height = (int)(HEIGHT / g->ray.perp_wall_dist);

    int draw_start = -line_height / 2 + HEIGHT / 2;
    if (draw_start < 0)
        draw_start = 0;

    int draw_end = line_height / 2 + HEIGHT / 2;
    if (draw_end >= HEIGHT)
        draw_end = HEIGHT - 1;
    
    mlx_texture_t *tex;
    if (g->ray.side == 0)
    {
        if (g->ray.step_x > 0)
            tex = g->tex_e;
        else
            tex = g->tex_w;
    }
    else
    {
        if (g->ray.step_y > 0)
            tex = g->tex_s;
        else
            tex = g->tex_n;
        
    }
    double wall_x;
    if(g->ray.side == 0)
        wall_x = g->player.y + g->ray.perp_wall_dist * g->ray.dir_y;
    else
        wall_x = g->player.x + g->ray.perp_wall_dist * g->ray.dir_x;
    wall_x -= floor(wall_x);
    int tex_x = (int)(wall_x * tex->width);
    double step = (double)tex->height / line_height;
    double tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
    for (int y = draw_start; y <= draw_end; y++)
    {
        int tex_y = (int)tex_pos;
        tex_pos += step;
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= (int)tex->height)
            tex_y = tex->height - 1;
        int i = (tex_y * tex->width + tex_x) * 4;
        uint8_t *p = tex->pixels + i;
        uint32_t color = (p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3]);
        mlx_put_pixel(g->frame, x, y, color);
    }
}

