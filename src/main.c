/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:46:56 by dogs              #+#    #+#             */
/*   Updated: 2026/01/08 17:49:41 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(int argc, char **argv)
{
    t_game game;
    (void)argc;
    (void)argv;
    init_game(&game);
    init_hooks(&game);
    
    mlx_loop(game.mlx); //causes leaks, check at campus.
    cleanup(&game);
    return (0);
}
