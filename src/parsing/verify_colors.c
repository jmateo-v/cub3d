#include "cub3d.h"

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
	if (alt_atoi(color, dst) == -1)
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
		while (line[*i] && ft_isspace(line[*i]))
			(*i)++;
		start = *i;
		while (line[*i] && line[*i] != ',')
		{
			if (!ft_isdigit(line[*i]) && line[*i] != '+'
				&& !ft_isspace(line[*i]))
				error_exit(ERR_VALID_COLOR);
			(*i)++;
		}
		save_colors(g, ft_substr(line, start, *i - start), &found, 1);
		if (line[*i] != '\0')
			(*i)++;
	}
	g->parse.f = true;
}

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
		while (line[*i] && ft_isspace(line[*i]))
			(*i)++;
		start = *i;
		while (line[*i] && line[*i] != ',')
		{
			if (!ft_isdigit(line[*i]) && line[*i] != '+'
				&& !ft_isspace(line[*i]))
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
		g->map.floor_color = ((uint32_t)0xFF << 24)
			| ((uint32_t)g->parse.floor_b << 16)
			| ((uint32_t)g->parse.floor_g << 8) | (uint32_t)g->parse.floor_r;
	}
	else if (line[*i] == 'C')
	{
		(*i)++;
		if (g->parse.c == true || line[*i] == '\0')
			error_exit(ERR_NO_COLOR);
		while (line[*i] && ft_isspace(line[*i]))
			(*i)++;
		obtain_ceiling_colors(g, line, i);
		g->map.ceiling_color = ((uint32_t)0xFF << 24)
			| ((uint32_t)g->parse.ceiling_b << 16)
			| ((uint32_t)g->parse.ceiling_g << 8)
			| (uint32_t)g->parse.ceiling_r;
	}
}
