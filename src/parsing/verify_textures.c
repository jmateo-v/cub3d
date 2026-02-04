#include "cub3d.h"

void	save_texture_n(t_game *g, char *line, int *i)
{
	int	start;

	start = 0;
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
}

void	save_texture_s(t_game *g, char *line, int *i)
{
	int	start;

	start = 0;
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
}

void	save_texture_e(t_game *g, char *line, int *i)
{
	int	start;

	start = 0;
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
}

void	save_texture_w(t_game *g, char *line, int *i)
{
	int	start;

	start = 0;
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
}

void	verify_texture(t_game *g, char *line, int *i)
{
	if (line[*i] == 'N' && line[*i + 1] && line[*i + 1] == 'O')
		save_texture_n(g, line, i);
	else if (line[*i] == 'S' && line[*i + 1] && line[*i + 1] == 'O')
		save_texture_s(g, line, i);
	else if (line[*i] == 'E' && line[*i + 1] && line[*i + 1] == 'A')
		save_texture_e(g, line, i);
	else if (line[*i] == 'W' && line[*i + 1] && line[*i + 1] == 'E')
		save_texture_w(g, line, i);
	else
		error_exit(ERR_VALID_CHARS);
}
