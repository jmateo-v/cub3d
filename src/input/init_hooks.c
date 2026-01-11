/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:52:34 by dogs              #+#    #+#             */
/*   Updated: 2026/01/08 17:50:43 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_hooks(t_game *g)
{
    mlx_key_hook(g->mlx, handle_keys, g);
    mlx_loop_hook(g->mlx, game_loop, g);
    mlx_close_hook(g->mlx, close_game, g);
}