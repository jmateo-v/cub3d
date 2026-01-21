#include "cub3d.h"

//THIS FILE KILLED THE NORM, f for it.

//FOR TESTING PURPOSES, COPY_TMP_MAP COPIES TO THE GRID VARIABLE
//INSIDE OF MAP STRUCT. HOWEVER, COPY_TMP_MAP DOESNT PRODUCE A FINAL
//VERSION OF THE MAP, KEEP THIS IN MIND FOR THE FUTURE.

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
				&& g->parse.arr_file[pos][j] != 'N' && !ft_isspace(g->parse.arr_file[pos][j])
				&& g->parse.arr_file[pos][j] != 'D')
				error_exit(ERR_VALID_MAP);
			else if (g->parse.arr_file[pos][j] == 'N' || g->parse.arr_file[pos][j] == 'S'
				|| g->parse.arr_file[pos][j] == 'W' || g->parse.arr_file[pos][j] == 'E')
                player_found++;
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
	//TMP_MAP ALREADY STORED AND BASIC CHECKS DONE, NOW HAVE TO DO FLOODFILL AND
	//CREATE THE FINAL VERSION OF THE MAP (THE ONE WITH CORNERS FIXED). DO THIS HERE:
}

void	save_colors(t_game *g, char *color, int *found, int location)
{
	int	*dst;

	dst = 0;
	if (!color)
		error_exit(ERR_VALID_COLOR);
	if (location == 1)
		dst = &g->parse.floor_r;
	else if (location == 2)
		dst = &g->parse.ceiling_r;
	if (dst == 0)
		error_exit(ERR_VALID_COLOR);
	if (*found == 1)
		dst++;
	else if (*found == 2)
		dst = dst + 2;
	if (atoi_v2(color, dst) == -1)
		error_exit(ERR_VALID_COLOR);
    (*found)++;
	free(color);
}

void	obtain_floor_colors(t_game *g, char *line, int *i)
{
	int	start;
	int	found;

	found = 0;
	while (1)
	{
		if (line[*i] == '\0' && found == 3)
			break ;
		else if (line[*i] == ',' || (found >= 3 && line[*i] != '\0'))
			error_exit(ERR_VALID_COLOR);
		start = *i;
		while (line[*i] && line[*i] != ',')
		{
			if (found < 2 && (line[*i] < '0' || line[*i] > '9') && line[*i] != '+')
				error_exit(ERR_VALID_COLOR);
			else if (found == 2 && (line[*i] < '0' || line[*i] > '9')
				&& line[*i] != '+' && !ft_isspace(line[*i]))
				error_exit(ERR_VALID_COLOR);
			(*i)++;
		}
		save_colors(g, ft_substr(line, start, *i - start), &found, 1);
		if (line[*i] != '\0')
			(*i)++;
	}
	g->parse.f = true;
}

//MAKE SURE TO CONVERT COLORS AND SAVE THE RESULT TO THE MAP STRUCT BEFORE
//EXITING THE OBTAIN COLORS FUNCTIONS, ALSO SAVE COLOR VALUES TO PARSE STRUCT INSTEAD OF MAP

//TRAILING SPACES ARE ONLY ACCEPTED ON THE LAST NUMBER, NOT ON OTHERS.

void	obtain_ceiling_colors(t_game *g, char *line, int *i)
{
	int	start;
	int	found;

	found = 0;
	while (1)
	{
		if (line[*i] == '\0' && found == 3)
			break ;
		else if (line[*i] == ',' || (found >= 3 && line[*i] != '\0'))
			error_exit(ERR_VALID_COLOR);
		start = *i;
		while (line[*i] && line[*i] != ',')
		{
			if (found < 2 && (line[*i] < '0' || line[*i] > '9') && line[*i] != '+')
                error_exit(ERR_VALID_COLOR);
			else if (found == 2 && (line[*i] < '0' || line[*i] > '9')
				&& line[*i] != '+' && !ft_isspace(line[*i]))
				error_exit(ERR_VALID_COLOR);
			(*i)++;
		}
		save_colors(g, ft_substr(line, start, *i - start), &found, 2);
		if (line[*i] != '\0')
			(*i)++;
	}
	g->parse.c = true;
}

void	verify_colors(t_game *g, char *line, int *i)
{
	if (line[*i] == 'F')
	{
		(*i)++;
		if (g->parse.f == true || line[*i] == '\0')
			error_exit(ERR_NO_COLOR);
		while (line[*i] && ft_isspace(line[*i]))
			(*i)++;
		obtain_floor_colors(g, line, i);
		g->map.floor_color = ((uint32_t)g->parse.floor_r << 16)
			| ((uint32_t)g->parse.floor_g << 8)
			| (uint32_t)g->parse.floor_b;
		printf("\n\nDEBUG PRINTF: value of floor_color: %X\n",g->map.floor_color);
	}
	else if (line[*i] == 'C')
	{
		(*i)++;
		if (g->parse.c == true || line[*i] == '\0')
			error_exit(ERR_NO_COLOR);
		while (line[*i] && ft_isspace(line[*i]))
			(*i)++;
		obtain_ceiling_colors(g, line, i);
		g->map.ceiling_color = ((uint32_t)g->parse.ceiling_r << 16)
			| ((uint32_t)g->parse.ceiling_g << 8)
			| (uint32_t)g->parse.ceiling_b;
		printf("\n\nDEBUG PRINTF: value of ceiling_color: %X\n",g->map.ceiling_color);
	}
}

void	verify_texture(t_game *g, char *line, int *i)
{
	int	start;

	start = 0;
	if (line[*i] == 'N' && line[*i + 1] && line[*i + 1] == 'O')
	{
		*i = *i + 2;
		if (g->parse.no == true || line[*i] == '\0')
			error_exit(ERR_NO_TEXTURE);
		while (line[*i] && ft_isspace(line[*i]))
			(*i)++;
		start = *i;
		while (line[*i] && !ft_isspace(line[*i]))
			(*i)++;
		g->map.tex_n = ft_substr(line, start, *i - start);
		if (!g->map.tex_n)
			error_exit(ERR_TEXTURE_MALLOC);
		while (line[*i])
		{
			if (!ft_isspace(line[*i]))
				error_exit(ERR_VALID_TEXTURE);
			(*i)++;
		}
		g->parse.no = true;
		//printf("\n\nDEBUG PRINTF, VAL OF TEXTURE_NO: %s\n",g->map.tex_n);
	}
	else if (line[*i] == 'S' && line[*i + 1] && line[*i + 1] == 'O')
	{
		*i = *i + 2;
		if (g->parse.so == true || line[*i] == '\0')
			error_exit(ERR_NO_TEXTURE);
		while (line[*i] && ft_isspace(line[*i]))
			(*i)++;
		start = *i;
		while (line[*i] && !ft_isspace(line[*i]))
			(*i)++;
		g->map.tex_s = ft_substr(line, start, *i - start);
		if (!g->map.tex_s)
			error_exit(ERR_TEXTURE_MALLOC);
		while (line[*i])
		{
			if (!ft_isspace(line[*i]))
				error_exit(ERR_VALID_TEXTURE);
			(*i)++;
		}
		g->parse.so = true;
		//printf("\n\nDEBUG PRINTF, VAL OF TEXTURE_SO: %s\n",g->map.tex_s);
	}
	else if (line[*i] == 'E' && line[*i + 1] && line[*i + 1] == 'A')
	{
		*i = *i + 2;
		if (g->parse.ea == true || line[*i] == '\0')
			error_exit(ERR_NO_TEXTURE);
		while (line[*i] && ft_isspace(line[*i]))
			(*i)++;
		start = *i;
		while (line[*i] && !ft_isspace(line[*i]))
			(*i)++;
		g->map.tex_e = ft_substr(line, start, *i - start);
		if (!g->map.tex_e)
			error_exit(ERR_TEXTURE_MALLOC);
		while (line[*i])
		{
			if (!ft_isspace(line[*i]))
				error_exit(ERR_VALID_TEXTURE);
			(*i)++;
		}
		g->parse.ea = true;
		//printf("\n\nDEBUG PRINTF, VAL OF TEXTURE_EA: %s\n",g->map.tex_e);
	}
	else if (line[*i] == 'W' && line[*i + 1] && line[*i + 1] == 'E')
	{
		*i = *i + 2;
		if (g->parse.we == true || line[*i] == '\0')
			error_exit(ERR_NO_TEXTURE);
		while (line[*i] && ft_isspace(line[*i]))
			(*i)++;
		start = *i;
		while (line[*i] && !ft_isspace(line[*i]))
			(*i)++;
		g->map.tex_w = ft_substr(line, start, *i - start);
		if (!g->map.tex_w)
			error_exit(ERR_TEXTURE_MALLOC);
		while (line[*i])
		{
			if (!ft_isspace(line[*i]))
				error_exit(ERR_VALID_TEXTURE);
            (*i)++;
		}
		g->parse.we = true;
		//printf("\n\nDEBUG PRINTF, VAL OF TEXTURE_WE: %s\n",g->map.tex_w);
	}
	error_exit(ERR_VALID_CHARS);
}
