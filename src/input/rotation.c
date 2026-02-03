/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:39:47 by dogs              #+#    #+#             */
/*   Updated: 2026/02/03 11:22:34 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_camera(t_game *g, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->player.dir_x;
	old_plane_x = g->player.plane_x;
	g->player.dir_x = g->player.dir_x * cos(angle)
		- g->player.dir_y * sin(angle);
	g->player.dir_y = old_dir_x * sin(angle)
		+ g->player.dir_y * cos(angle);
	g->player.plane_x = g->player.plane_x * cos(angle)
		- g->player.plane_y * sin(angle);
	g->player.plane_y = old_plane_x * sin(angle)
		+ g->player.plane_y * cos(angle);
}
