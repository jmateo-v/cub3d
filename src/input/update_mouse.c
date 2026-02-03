/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 12:17:04 by dogs              #+#    #+#             */
/*   Updated: 2026/02/03 11:21:56 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_mouse(t_game *g)
{
	int32_t	mx;
	int32_t	my;
	int32_t	delta_x;

	mlx_get_mouse_pos(g->mlx, &mx, &my);
	if (mx >= 0 && mx < g->mlx->width && my >= 0 && my < g->mlx->height)
	{
		delta_x = mx - g->last_mouse_x;
		if (delta_x != 0)
			rotate_camera(g, delta_x * -MOUSE_ROT_SPEED);
	}
	mlx_set_mouse_pos(g->mlx, mx, my);
	g->last_mouse_x = mx;
}
