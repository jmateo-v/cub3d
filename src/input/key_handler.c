/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 18:56:54 by dogs              #+#    #+#             */
/*   Updated: 2026/01/10 19:55:12 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void handle_keypress(t_game *g, keys_t key)
{
    if (key == MLX_KEY_W)
        move_foward(g);
    if (key == MLX_KEY_S)
        move_backwards(g);
    if (key == MLX_KEY_A)
        move_left(g);
    if (key == MLX_KEY_D)
        move_right(g); 
    if (key == MLX_KEY_LEFT)
        rotate_left(g);
    if (key == MLX_KEY_RIGHT)
        rotate_right(g);
}
void handle_keys(mlx_key_data_t keydata, void *param)
{
    t_game *g = (t_game *)param;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        close_game(g);
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
        handle_keypress(g, keydata.key);
}