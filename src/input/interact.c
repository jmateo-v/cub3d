/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:44:23 by jmateo-v          #+#    #+#             */
/*   Updated: 2026/01/14 17:02:47 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
static float get_d_vector(t_game *g, int index)
{
	float px;
	float py;
	float dx;
	float dy;

	px = (float)g->player.x;
	py = (float)g->player.y;
	dx = (g->doors[index].x + 0.5f) - px;
	dy = (g->doors[index].y + 0.5f) - py;
	return (dx*dx + dy*dy);
}
void interact(t_game *g)
{
	int best;
	float best_d_vector;
	int i;
	float d_vector;

	if (!g || g->n_doors <= 0)
		return ;
	best = -1;
	best_d_vector = FLT_MAX;
	i = 0;
	while (i < g->n_doors)
	{
		d_vector = get_d_vector(g, i);
		if (d_vector <= INTERACT_REACH && d_vector < best_d_vector)
		{
			best = i;
			best_d_vector = d_vector;
		}
		i++;
	}
	if (best >= 0)
		g->doors[best].open = !g->doors[best].open;
}
