#include "cub3d.h"

void	init_parse(t_game *g)
{
	g->parse.floor_r = 0;
	g->parse.floor_g = 0;
	g->parse.floor_b = 0;
	g->parse.ceiling_r = 0;
	g->parse.ceiling_g = 0;
	g->parse.ceiling_b = 0;
	g->parse.c = false;
	g->parse.f = false;
	g->parse.no = false;
	g->parse.so = false;
	g->parse.we = false;
	g->parse.ea = false;
	g->parse.map = false;
	g->parse.file_fd = -1;
	g->parse.arr_file = NULL;
}

//A FILE JUST CALLED .CUB IS VALID, LIKELY WRONG, BUT DOUBLE CHECK.

int	check_valid_file(char *str, t_parse *parse)
{
	char	*tmp;

	if (!str)
		return (-1);
	tmp = str;
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
		error_exit("Error: inside copy_file");
	/*
	//DEBUG PRINTF, REMOVE LATER.
    printf("\n\nDEBUG PRINTF: PRINTING arr_file: \n");
    int     i = 0;
    while (g->parse.arr_file[i])
    {
		printf("%s\n",g->parse.arr_file[i]);
		i++;
    }
    //EVERYTHING ABOVE ARE TEST PRINTFS, REMOVE.
	*/
}
