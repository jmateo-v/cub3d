#include "cub3d.h"

//FOR TESTING PURPOSES, COPY_TMP_MAP COPIES TO THE GRID VARIABLE
//INSIDE OF MAP STRUCT. HOWEVER, COPY_TMP_MAP MIGHT NOT BE THE FINAL
//VERSION OF THE MAP, KEEP THIS IN MIND FOR THE FUTURE.
//
//ONLY THE PLAYER MAP MATTERS FOR THE FLOODFILL, EVERY OTHER ISLAND
//WONT BE TESTED, VERIFY THIS IS CORRECT. HOWEVER THEY STILL SHOW
//UP ON THE MINIMAP (THEY AREN'T RENDERED BECAUSE NO RAYS EVER TOUCH THEM).

void	init_player(t_game *g, int x, int y, int pos)
{
	g->player.x = (double)x + 0.5;
	g->player.y = (double)y + 0.5;
	g->player.dir_x = 0.0;
	g->player.dir_y = 0.0;
	g->player.plane_x = 0.0;
	g->player.plane_y = 0.0;
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

void	copy_tmp_map(t_game *g, int pos)
{
	int	player_found;
	int	i;
	int	j;
	int	len;

	player_found = 0;
	i = 0;
	j = 0;
	len = get_array_len(g->parse.arr_file);
	//THIS TMP COPY OF MAP SHOULD BE ON THE PARSE STRUCT, NOT ON map.GRID
	g->map.grid = (char **)ft_calloc(len - pos + 1, sizeof(char *));
	if (!g->map.grid)
		error_exit(ERR_MAP_MALLOC);
	while (pos < len)
	{
		j = 0;
		g->map.grid[i] = (char *)ft_calloc((ft_strlen(g->parse.arr_file[pos]) + 1), sizeof(char));
		if (!g->map.grid[i])
			error_exit(ERR_MAP_MALLOC);
		while (g->parse.arr_file[pos][j])
		{
			//MOVE THIS TO AN AUX FUNCTION THAT CHECKS ALL MAP/PLAYER VALID VALUES PLS.
			if (g->parse.arr_file[pos][j] != 'N' && g->parse.arr_file[pos][j] != 'S'
				&& g->parse.arr_file[pos][j] != 'W' && g->parse.arr_file[pos][j] != 'E'
				&& g->parse.arr_file[pos][j] != '1' && g->parse.arr_file[pos][j] != '0'
				&& g->parse.arr_file[pos][j] != 'N' && g->parse.arr_file[pos][j] != ' '
				&& g->parse.arr_file[pos][j] != 'D')
				error_exit(ERR_VALID_MAP);
			else if (g->parse.arr_file[pos][j] == 'N' || g->parse.arr_file[pos][j] == 'S'
				|| g->parse.arr_file[pos][j] == 'W' || g->parse.arr_file[pos][j] == 'E')
			{
				player_found++;
				init_player(g, j, i, pos);
			}
			if (player_found > 1)
				error_exit(ERR_MORE_PLAYER);
			g->map.grid[i][j] = g->parse.arr_file[pos][j];
			j++;
		}
		i++;
		pos++;
	}
	if (player_found == 0)
		error_exit(ERR_NO_PLAYER);
}

void	verify_map(t_game *g, int pos)
{
	if (g->parse.no == false || g->parse.so == false || g->parse.we == false
		|| g->parse.ea == false || g->parse.f == false || g->parse.c == false)
		error_exit(ERR_MISSING_VALS);
	copy_tmp_map(g, pos);
	//TMP_MAP ALREADY STORED AND BASIC CHECKS DONE, NOW HAVE TO DO FLOODFILL
	//AND MAYBE CREATE THE FINAL VERSION OF THE MAP. DO THIS HERE:
}
