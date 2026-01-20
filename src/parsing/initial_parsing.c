#include "cub.h"

int	init_parse(t_game **g)
{
	(*g)->parse = (t_parse *)malloc(sizeof(t_parse));
	if (!(*g)->parse)
		return (-1);
        /*(*g)->parse->map_values = (t_map_values *)malloc(sizeof(t_map_values));
        if (!(*g)->parse->map_values)
                return (printf("no workeo el malloc jo\n"), -1);
        (*g)->parse->map_values->tmp_map = NULL;
        (*g)->parse->map_values->final_map = NULL;
        (*g)->parse->map_values->texture_no = NULL;
        (*g)->parse->map_values->texture_so = NULL;
        (*g)->parse->map_values->texture_ea = NULL;
        (*g)->parse->map_values->texture_we = NULL;
        (*g)->parse->map_values->floor_r = 0;
        (*g)->parse->map_values->floor_g = 0;
        (*g)->parse->map_values->floor_b = 0;
        (*g)->parse->map_values->ceiling_r = 0;
        (*g)->parse->map_values->ceiling_g = 0;
        (*g)->parse->map_values->ceiling_b = 0;*/
	(*g)->parse->c = false;
	(*g)->parse->f = false;
	(*g)->parse->no = false;
	(*g)->parse->so = false;
	(*g)->parse->we = false;
	(*g)->parse->ea = false;
	(*g)->parse->map = false;
	(*g)->parse->file_fd = -1;
	(*g)->parse->arr_file = NULL;
	//(*g)->parse->copy_file = NULL;
	return (0);
}

//A FILE JUST CALLED .CUB IS VALID, LIKELY WRONG, BUT DOUBLE CHECK.

int	check_valid_file(char *str, t_parse **parse)
{
	char	*tmp;

	tmp = str;
	while (*tmp && *tmp != '.')
		++tmp;
	if (*tmp != '.')
		return (-1);
	if (ft_strncmp(tmp, ".cub", 4) || (ft_strlen(tmp) != 4))
		return (-1);
	(*parse)->file_fd = open(str, O_RDONLY);
	if ((*parse)->file_fd < 0)
		return (-1);
	return (0);
}

int	copy_file(t_parse **parse)
{
	char	*line;
	char	*copy_file;

	line = "";
	copy_file = NULL;
	while (line)
	{
		line = get_next_line((*parse)->file_fd);
		if (!line)
			break ;
		copy_file = ft_strjoin(copy_file, line);
		free(line);
		if (!copy_file)
			return (close((*parse)->file_fd), -1);
	}
	close((*parse)->file_fd);
	(*parse)->arr_file = ft_split(copy_file, '\n');
	if (!(*parse)->arr_file)
		return (free(copy_file), -1);
	return (free(copy_file), 0);
}

void	initial_parsing(t_game *g, int argc, char **argv)
{
	if (argc != 2)
		error_exit(ERR_ARG_COUNT);
	if (init_parse(g) == -1)
		error_exit("Error: initializing parse struct");
	if (check_valid_file(argv[1], &g->parse) == -1)
		error_exit(ERR_VALID_MAP);
	if (copy_file(&g->parse) == -1)
		error_exit("Error: copying file");
	//DEBUG PRINTF, REMOVE LATER.
    printf("\n\nDEBUG PRINTF: PRINTING arr_file: \n");
    int     i = 0;
    while (g->parse->arr_file[i])
    {
		printf("%s\n",g->parse->arr_file[i]);
		i++;
    }
    //EVERYTHING ABOVE ARE TEST PRINTFS, REMOVE.
}
