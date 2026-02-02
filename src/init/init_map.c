/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:53:11 by jmateo-v          #+#    #+#             */
/*   Updated: 2026/01/19 15:31:11 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *g, int x, int y, int pos)
{
	g->player.x = (double)x + 0.5;
	g->player.y = (double)y + 0.5;
	if (g->parse.arr_file[pos][x] == 'N')
	{
		g->player.dir_y = -1.0;
		g->player.plane_x = -0.66;
	}
	else if (g->parse.arr_file[pos][x] == 'S')
	{
		g->player.dir_y = 1.0;
		g->player.plane_x = 0.66;
	}
	else if (g->parse.arr_file[pos][x] == 'W')
	{
		g->player.dir_x = -1.0;
		g->player.plane_y = 0.66;
	}
	else if (g->parse.arr_file[pos][x] == 'E')
	{
		g->player.dir_x = 1.0;
		g->player.plane_y = -0.66;
	}
}

void	verify_line(t_game *g, char *line, int pos)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		verify_texture(g, line, &i);
	else if (line[i] == 'F' || line[i] == 'C')
		verify_colors(g, line, &i);
	else if (line[i] == '1' || line[i] == '0' || line[i] == 'N'
		|| line[i] == 'S' || line[i] == 'W' || line[i] == 'E' || line[i] == 'D')
	{
		verify_map(g, pos);
		g->parse.map = true;
		return ;
	}
	else
		error_exit(ERR_VALID_CHARS);
}

void	init_map(t_game *g)
{
	int	i;

	i = 0;
	while (g->parse.arr_file[i])
	{
		verify_line(g, g->parse.arr_file[i], i);
		if (g->parse.map == true)
			break ;
		i++;
	}
}
