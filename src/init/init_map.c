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
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		verify_texture(g, line, &i);
	else if (line[i] == 'F' || line[i] == 'C')
		verify_colors(g, line, &i);
	else if (line[i] == '1' || line[i] == '0' || line[i] == 'N'
		|| line[i] == 'S' || line[i] == 'W' || line[i] == 'E' || line[i] == 'D')
	{
		verify_map(g, pos);
		g->parse.map = true;
		return ;
	}
	else
		error_exit(ERR_VALID_CHARS);
}

//MAYBE INIT VARIABLES OF MAP STRUCT FOR SAFETY PURPOSES.

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
	/*
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
	printf("Val of height: %d\n",g->map.height);
	printf("Val of width: %d\n",g->map.width);
    printf("\nPrinting vals of tmp_map: \n");
    int     j = 0;
    if (!g->map.grid || !g->map.grid[0])
        error_exit("no map found");
    while (g->map.grid[j])
    {
        printf("'%s'\n", g->map.grid[j]);
        j++;
    }
    //EVERYTHING ABOVE ARE TEST PRINTFS, REMOVE LATER.
	*/
}
