/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:36:31 by dogs              #+#    #+#             */
/*   Updated: 2026/02/03 11:31:00 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_door(t_door *d, float dt)
{
	if (d->open)
	{
		if (d->prog < 1.0f)
			d->prog += d->speed * dt;
		if (d->prog > 1.0f)
			d->prog = 1.0f;
	}
	else
	{
		if (d->prog > 0.0f)
			d->prog -= d->speed * dt;
		if (d->prog < 0.0f)
			d->prog = 0.0f;
	}
}

void	update_doors(t_game *g, float dt)
{
	int	i;

	i = 0;
	while (i < g->n_doors)
	{
		update_door(&g->doors[i], dt);
		i++;
	}
}

bool	is_door_closed(t_game *g, int x, int y)
{
	int	i;

	i = 0;
	while (i < g->n_doors)
	{
		if (g->doors[i].x == x && g->doors[i].y == y)
		{
			if (g->doors[i].prog <= 0.1f)
				return (true);
			if (g->doors[i].prog >= 0.9f)
				return (false);
			return (true);
		}
		i++;
	}
	return (false);
}

int	find_door_index(t_game *g, int x, int y)
{
	int	i;

	i = 0;
	while (i < g->n_doors)
	{
		if (g->doors[i].x == x && g->doors[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}
