/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 19:09:45 by dogs              #+#    #+#             */
/*   Updated: 2026/02/03 11:20:20 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_loop(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	update_mouse(g);
	update_doors(g, DELTA_TIME);
	anim_sprites(g);
	render_frame(g);
	render_sprites(g);
}
