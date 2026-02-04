/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrlinei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:37:11 by adrlinei          #+#    #+#             */
/*   Updated: 2026/02/04 20:37:13 by adrlinei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_line(t_game *g, int x, int i)
{
	int	j;

	j = 0;
	while (g->parse.arr_file[x][j])
	{
		if (g->parse.arr_file[x][j] != 'N' && g->parse.arr_file[x][j] != 'S'
			&& g->parse.arr_file[x][j] != 'W' && g->parse.arr_file[x][j] != 'E'
			&& g->parse.arr_file[x][j] != '1' && g->parse.arr_file[x][j] != '0'
			&& g->parse.arr_file[x][j] != 'N' && g->parse.arr_file[x][j] != ' '
			&& g->parse.arr_file[x][j] != 'D' && g->parse.arr_file[x][j] != 'X')
			error_exit(ERR_VALID_MAP);
		else if (g->parse.arr_file[x][j] == 'N'
			|| g->parse.arr_file[x][j] == 'S' || g->parse.arr_file[x][j] == 'W'
			|| g->parse.arr_file[x][j] == 'E')
		{
			g->parse.player_found++;
			if (g->parse.player_found > 1)
				error_exit(ERR_MORE_PLAYER);
			init_player(g, j, i, x);
		}
		g->map.grid[i][j] = g->parse.arr_file[x][j];
		j++;
	}
}

void	copy_map(t_game *g, int pos)
{
	int	i;
	int	len;

	i = 0;
	len = get_array_len(g->parse.arr_file);
	g->map.grid = (char **)ft_calloc(len - pos + 1, sizeof(char *));
	if (!g->map.grid)
		error_exit(ERR_MAP_MALLOC);
	while (pos < len)
	{
		g->map.grid[i] = ft_calloc((ft_strlen(g->parse.arr_file[pos]) + 1), 1);
		if (!g->map.grid[i])
			error_exit(ERR_MAP_MALLOC);
		copy_line(g, pos, i);
		i++;
		pos++;
	}
	if (g->parse.player_found == 0)
		error_exit(ERR_NO_PLAYER);
	free_array(g->parse.arr_file);
}

char	**copy_flood_map(t_game *g)
{
	char	**dst;
	int		i;
	int		j;
	int		len;

	i = 0;
	len = get_array_len(g->map.grid);
	dst = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!dst)
		error_exit(ERR_MAP_MALLOC);
	while (g->map.grid[i])
	{
		j = 0;
		dst[i] = (char *)ft_calloc(ft_strlen(g->map.grid[i]) + 1, sizeof(char));
		if (!dst[i])
			error_exit(ERR_MAP_MALLOC);
		while (g->map.grid[i][j])
		{
			dst[i][j] = g->map.grid[i][j];
			j++;
		}
		i++;
	}
	return (dst);
}

void	floodfill(t_game *g, char **flood_map, int x, int y)
{
	if (x < 0 || x > (int)ft_strlen(flood_map[y]) || y < 0
		|| y > g->map.height || flood_map[y][x] == ' ')
		error_exit(ERR_MAP_OPEN);
	if (flood_map[y][x] == 'F' || flood_map[y][x] == '1')
		return ;
	else if (flood_map[y][x] == '0' || flood_map[y][x] == 'X'
		|| flood_map[y][x] == 'D' || flood_map[y][x] == 'N'
		|| flood_map[y][x] == 'S' || flood_map[y][x] == 'W'
		|| flood_map[y][x] == 'E')
		flood_map[y][x] = 'F';
	floodfill(g, flood_map, x, y + 1);
	floodfill(g, flood_map, x, y - 1);
	floodfill(g, flood_map, x + 1, y);
	floodfill(g, flood_map, x - 1, y);
}

void	verify_map(t_game *g, int pos)
{
	char	**flood_map;
	int		i;
	int		width;

	flood_map = NULL;
	i = 0;
	width = 0;
	if (g->parse.no == false || g->parse.so == false || g->parse.we == false
		|| g->parse.ea == false || g->parse.f == false || g->parse.c == false)
		error_exit(ERR_MISSING_VALS);
	copy_map(g, pos);
	while (g->map.grid[g->map.height])
		g->map.height++;
	while (g->map.grid[i])
	{
		width = ft_strlen(g->map.grid[i]);
		if (width > g->map.width)
			g->map.width = width;
		i++;
	}
	flood_map = copy_flood_map(g);
	if (!flood_map)
		error_exit(ERR_MAP_MALLOC);
	floodfill(g, flood_map, (int)(g->player.x - 0.5), (int)(g->player.y - 0.5));
	free_array(flood_map);
}
