/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrlinei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:36:34 by adrlinei          #+#    #+#             */
/*   Updated: 2026/02/04 20:36:36 by adrlinei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_map(t_game *g)
{
	g->player.x = 0.0;
	g->player.y = 0.0;
	g->player.dir_x = 0.0;
	g->player.dir_y = 0.0;
	g->player.plane_x = 0.0;
	g->player.plane_y = 0.0;
	g->map.grid = NULL;
	g->map.width = 0;
	g->map.height = 0;
	g->map.floor_color = 0;
	g->map.ceiling_color = 0;
	g->map.tex_n = NULL;
	g->map.tex_s = NULL;
	g->map.tex_w = NULL;
	g->map.tex_e = NULL;
}

void	init_parse(t_game *g)
{
	g->parse.floor_r = 0;
	g->parse.floor_g = 0;
	g->parse.floor_b = 0;
	g->parse.ceiling_r = 0;
	g->parse.ceiling_g = 0;
	g->parse.ceiling_b = 0;
	g->parse.player_found = 0;
	g->parse.c = false;
	g->parse.f = false;
	g->parse.no = false;
	g->parse.so = false;
	g->parse.we = false;
	g->parse.ea = false;
	g->parse.map = false;
	g->parse.file_fd = -1;
	g->parse.arr_file = NULL;
	init_player_map(g);
}

int	check_valid_file(char *str, t_parse *parse)
{
	char	*tmp;

	if (!str || !str[0])
		return (-1);
	tmp = ft_strrchr(str, '/');
	if (tmp)
	{
		tmp++;
		if (*tmp == '.')
			return (-1);
	}
	tmp = str;
	if (*tmp == '.')
		return (-1);
	while (*tmp && *tmp != '.')
		++tmp;
	if (*tmp != '.')
		return (-1);
	if (ft_strncmp(tmp, ".cub", 4) || (ft_strlen(tmp) != 4))
		return (-1);
	parse->file_fd = open(str, O_RDONLY);
	if (parse->file_fd < 0)
		return (-1);
	return (0);
}

int	copy_file(t_parse *parse)
{
	char	*line;
	char	*copy_file;

	line = "";
	copy_file = NULL;
	while (line)
	{
		line = get_next_line(parse->file_fd);
		if (!line)
			break ;
		copy_file = alt_strjoin(copy_file, line);
		free(line);
		if (!copy_file)
			return (close(parse->file_fd), -1);
	}
	close(parse->file_fd);
	parse->arr_file = ft_split(copy_file, '\n');
	if (!parse->arr_file)
		return (free(copy_file), -1);
	return (free(copy_file), 0);
}

void	initial_parsing(t_game *g, int argc, char **argv)
{
	if (argc != 2)
		error_exit(ERR_ARG_COUNT);
	init_parse(g);
	if (check_valid_file(argv[1], &g->parse) == -1)
		error_exit(ERR_VALID_FILE);
	if (copy_file(&g->parse) == -1)
		error_exit(ERR_FILE_MALLOC);
}
