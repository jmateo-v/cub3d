#include "cub.h"

//REMOVE ASSIGNATIONS TO PASS NORM PLS.

int	init_parse(t_game **game)
{
	(*game)->parse = (t_parse *)malloc(sizeof(t_parse));
	if (!(*game)->parse)
		return (-1);
        /*(*parse)->map_values = (t_map_values *)malloc(sizeof(t_map_values));
        if (!(*parse)->map_values)
                return (printf("no workeo el malloc jo\n"), -1);
        (*parse)->map_values->tmp_map = NULL;
        (*parse)->map_values->final_map = NULL;
        (*parse)->map_values->texture_no = NULL;
        (*parse)->map_values->texture_so = NULL;
        (*parse)->map_values->texture_ea = NULL;
        (*parse)->map_values->texture_we = NULL;
        (*parse)->map_values->floor_r = 0;
        (*parse)->map_values->floor_g = 0;
        (*parse)->map_values->floor_b = 0;
        (*parse)->map_values->ceiling_r = 0;
        (*parse)->map_values->ceiling_g = 0;
        (*parse)->map_values->ceiling_b = 0;*/
	((*parse)->c = false, (*parse)->f = false, (*parse)->no = false);
	((*parse)->so = false, (*parse)->we = false, (*parse)->ea = false);
	(*parse)->map = false;
	(*parse)->arr_file = NULL;
	(*parse)->copy_file = NULL;
	return (0);
}

void	parsing(t_game *game, int argc, char **argv)
{
	if (argc != 2)
		error_exit(ERR_ARG_COUNT);
	if (init_parse(game) == -1)
		error_exit("error init parse struct");
}
