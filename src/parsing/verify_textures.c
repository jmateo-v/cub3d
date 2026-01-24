#include "cub3d.h"

//SIMPLIFYING THIS CLEANLY IS KINDA HARD, BUT IT'S COMING I SWEAR.

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
	else
		error_exit(ERR_VALID_CHARS);
}
