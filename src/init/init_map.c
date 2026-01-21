/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:53:11 by jmateo-v          #+#    #+#             */
/*   Updated: 2026/01/19 15:31:11 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	verify_line(t_game *g, char *line, int pos)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	//SHOULD MAKE A CHANGE TO THIS CONDITION, CHECK NEXT CHAR FOR MATCH TOO.
	//SO TO EACH ONE ADD && LINE[I + 1] && LINE[I + 1] == 'O/E/A'. THIS ALSO SIMPLIFIES FUNC.
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		verify_texture(g, line, &i);
	else if (line[i] == 'F' || line[i] == 'C')
		verify_colors(g, line, &i);
	else if (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == 'S'
		|| line[i] == 'W' || line[i] == 'E' || line[i] == 'D')
	{
		verify_map(g, pos);
		g->parse.map = true;
		return ;
	}
	else
		error_exit(ERR_VALID_CHARS);
}

void	init_map(t_game *g)
{
	int	i;

	i = 0;
	while (g->parse.arr_file[i])
	{
		verify_line(g, g->parse.arr_file[i], i);
		if (g->parse.map == true)
			break ;
		i++;
	}
	//THIS IS TO TEST IF EVERYTHING HAS BEEN COPIED PROPERLY, REMOVE LATER.
    printf("\nPrinting values of colors and textures\n");
    printf("RGB floor colors: %d %d %d\n",g->parse.floor_r,
    g->parse.floor_g, g->parse.floor_b);
    printf("RGB ceiling colors: %d %d %d\n",g->parse.ceiling_r,
    g->parse.ceiling_g, g->parse.ceiling_b);
    printf("Texture_no: %s\n",g->map.tex_n);
    printf("Texture_so: %s\n",g->map.tex_s);
    printf("Texture_ea: %s\n",g->map.tex_e);
    printf("Texture_we: %s\n",g->map.tex_w);
    printf("\nPrinting vals of tmp_map: \n");
    int     j = 0;
    if (!g->map.grid || !g->map.grid[0])
        error_exit("no map found");
    while (g->map.grid[j])
    {
        printf("%s\n", g->map.grid[j]);
        j++;
    }
    //EVERYTHING ABOVE ARE TEST PRINTFS, REMOVE LATER.
    g->map.height = 0;
    while (g->map.grid[g->map.height])
        g->map.height++;
	//THIS IS FOR TESTING PURPOSES, LIKELY NEEDS TO GET THE WIDTH OF LONGEST LINE.
    g->map.width = ft_strlen(g->map.grid[0]);
	/*static char *hardcoded_grid[] = {
        "1111111111",
        "1000000001",
        "1010000101",
        "1010000D01",
        "1000000101",
        "1000000001",
        "1010000101",
        "10011D1001",
        "1000000001",
        "1111111111",
        NULL
    };

    m->grid = hardcoded_grid;

    m->height = 0;
    while (hardcoded_grid[m->height])
        m->height++;

    m->width = ft_strlen(hardcoded_grid[0]);

    m->floor_color = 0xFF0000FF;
    m->ceiling_color = 0xFFFFFFFF;

    m->tex_n = "textures/placeholder.png";
    m->tex_s = "textures/placeholder_S.png";
    m->tex_w = "textures/placeholder_W.png";
    m->tex_e = "textures/placeholder_E.png";*/
	
}
