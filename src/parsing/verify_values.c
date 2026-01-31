#include "cub3d.h"

//FOR TESTING PURPOSES, COPY_TMP_MAP COPIES TO THE GRID VARIABLE
//INSIDE OF MAP STRUCT. HOWEVER, COPY_TMP_MAP MIGHT NOT BE THE FINAL
//VERSION OF THE MAP, KEEP THIS IN MIND FOR THE FUTURE.
//
//ONLY THE PLAYER MAP MATTERS FOR THE FLOODFILL, EVERY OTHER ISLAND
//WONT BE TESTED, VERIFY THIS IS CORRECT. HOWEVER THEY STILL SHOW
//UP ON THE MINIMAP (THEY AREN'T RENDERED BECAUSE NO RAYS EVER TOUCH THEM).
//
//IN CASE TEXTURES ARE INVALID, THERE ARE LEAKS, THIS IS BECAUSE THE
//MLX STRUCT IS INITIALIZED AND NOT FREED, TO FIX THIS, CLEANUP THE
//STRUCT BEFORE CALLING ERROR_EXIT FUNCTION.

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
	//printf("\nDEBUG PRINTF: val of dir.x: %f, val of dir.y: %f, val of plane.x: %f, val of plane.y: %f\n\n",g->player.dir_x,g->player.dir_y,g->player.plane_x,g->player.plane_y);
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
				&& g->parse.arr_file[pos][j] != 'D' && g->parse.arr_file[pos][j] != 'X')
				error_exit(ERR_VALID_MAP);
			else if (g->parse.arr_file[pos][j] == 'N' || g->parse.arr_file[pos][j] == 'S'
				|| g->parse.arr_file[pos][j] == 'W' || g->parse.arr_file[pos][j] == 'E')
			{
				player_found++;
				if (player_found > 1)
					error_exit(ERR_MORE_PLAYER);
				init_player(g, j, i, pos);
			}
			g->map.grid[i][j] = g->parse.arr_file[pos][j];
			j++;
		}
		i++;
		pos++;
	}
	if (player_found == 0)
		error_exit(ERR_NO_PLAYER);
}

char	**copy_flood_map(t_game *g)
{
	char	**dst;
	int	i;
	int	j;
	int	len;

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
	char **flood_map;
	int	i;
	int	width;

	flood_map = NULL;
	i = 0;
	width = 0;
	g->map.height = 0;
	if (g->parse.no == false || g->parse.so == false || g->parse.we == false
		|| g->parse.ea == false || g->parse.f == false || g->parse.c == false)
		error_exit(ERR_MISSING_VALS);
	copy_tmp_map(g, pos);
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
	/*
	//THIS IS TO PRINT THE FLOOD_MAP TO MAKE SURE FLOODFILL WORKS, REMOVE LATER.
	i = 0;
	printf("\nDEBUG PRINT: printing flood_map after floodfill:\n");
	while (flood_map[i])
	{
		printf("%s\n",flood_map[i]);
		i++;
	}
	//REMOVE TEST PRINTF ABOVE.
	*/
}
