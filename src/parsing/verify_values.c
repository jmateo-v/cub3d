#include "cub3d.h"

//A NORM MESS, BUT FUNCTIONAL.

int     copy_tmp_map(t_map_data **data, int pos)
{
        int     player_found;
        int     i;
        int     j;
        int     len;

        player_found = 0;
        i = 0;
        j = 0;
        len = get_array_len((*data)->arr_file);
        (*data)->map_values->tmp_map = (char **)ft_calloc(len - pos + 1, sizeof(char *));
        if (!(*data)->map_values->tmp_map)
                return (-1);
        while (pos < len)
        {
                j = 0;
                (*data)->map_values->tmp_map[i] = (char *)ft_calloc((ft_strlen((*data)->arr_file[pos]) + 1), sizeof(char));
                if (!(*data)->map_values->tmp_map[i])
                        return (-1);    //ALWAYS REMEMBER TO FREE ALL STRINGS OF TMP_MAP UNTIL THIS POINT, AND TMP_MAP ITSELF.
                while ((*data)->arr_file[pos][j])
                {
                        if ((*data)->arr_file[pos][j] != 'N' && (*data)->arr_file[pos][j] != 'S'
                                && (*data)->arr_file[pos][j] != 'W' && (*data)->arr_file[pos][j] != 'E'
                                && (*data)->arr_file[pos][j] != '1' && (*data)->arr_file[pos][j] != '0'
                                && (*data)->arr_file[pos][j] != 'N' && (*data)->arr_file[pos][j] != ' '
                                && ((*data)->arr_file[pos][j] < 9 || (*data)->arr_file[pos][j] > 11))
                                return (printf("Invalid chars found in map\n"), -1);    //FREE ALL STRINGS TMP_MAP AND ITSELF.
                        else if ((*data)->arr_file[pos][j] == 'N' || (*data)->arr_file[pos][j] == 'S'
                                || (*data)->arr_file[pos][j] == 'W' || (*data)->arr_file[pos][j] == 'E')
                                player_found++;
                        if (player_found > 1)
                                return (printf("More than one player found\n"), -1);    //FREE ALL STRINGS TMP_MAP AND ITSELF.
                        (*data)->map_values->tmp_map[i][j] = (*data)->arr_file[pos][j];
                        j++;
                }
                i++;
                pos++;
        }
        if (player_found == 0)
                return (printf("No player character found\n"), -1);
        return (0);
}

int     verify_map(t_map_data **data, int pos)
{
        if ((*data)->no == false || (*data)->so == false || (*data)->we == false
                || (*data)->ea == false || (*data)->f == false || (*data)->c == false)
                return (printf("Missing textures/colors\n"), -1);       //MISSING VALUES WHEN FIRST MAP CHARS FOUND.
        if (copy_tmp_map(data, pos) == -1)
                return (-1);    //EITHER WRONG VALUES OR MORE THAN ONE PLAYER FOUND IN MAP.
        //TMP_MAP ALREADY STORED AND BASIC CHECKS DONE, NOW HAVE TO DO FLOODFILL AND
        //CREATE THE FINAL VERSION OF THE MAP (THE ONE WITH CORNERS FIXED). DO THIS HERE:
        return (0);
}

int     save_cols(t_map_data **data, char *color, int *found, int location)
{
        int     *dst;

        dst = 0;
        if (!color)
                return (-1);
        if (location == 1)
                dst = &(*data)->map_values->floor_r;
        else if (location == 2)
                dst = &(*data)->map_values->ceiling_r;
        if (dst == 0)
                return (free(color), -1);
        if (*found == 1)
                dst++;
        else if (*found == 2)
                dst = dst + 2;
        if (atoi_v2(color, dst) == -1)
                return (free(color), -1);
        return ((*found)++, free(color), 0);
}

int     obtain_floor_colors(t_map_data **data, char *line, int *i)
{
        int     start;
        int     found;

        found = 0;
        while (1)
        {
                if (line[*i] == '\0' && found == 3)
                        break ;         //ALL 3 COLORS WERE FOUND AND SAVED PROPERLY, NOTHING ELSE IN STRING.
                else if (line[*i] == ',' || (found >= 3 && line[*i] != '\0'))
                        return (-1);    //MORE THAN ONE COMMA BETWEEN VALS OR MORE THAN 3 VALS, SO ERROR.
                start = *i;
                while (line[*i] && line[*i] != ',')
                {
                        //TRAILING SPACES ARE ONLY ACCEPTED ON THE LAST NUMBER, NOT ON THE OTHERS.
                        if (found < 2 && (line[*i] < '0' || line[*i] > '9') && line[*i] != '+')
                                return (-1);
                        else if (found == 2 && (line[*i] < '0' || line[*i] > '9')
                                && line[*i] != '+' && line[*i] != ' ' && (line[*i] < 9 || line[*i] > 11))
                                return (-1);
                        (*i)++;
                }
                if (save_cols(data, ft_substr(line, start, *i - start), &found, 1) == -1)
                        return (-1);
                if (line[*i] != '\0')
                        (*i)++;         //SKIPS THE CURRENT ',' AT THE LINE.
        }
        return ((*data)->f = true, 0);
}

int     obtain_ceiling_colors(t_map_data **data, char *line, int *i)
{
        int     start;
        int     found;

        found = 0;
        while (1)
        {
                if (line[*i] == '\0' && found == 3)
                        break ;         //ALL 3 COLORS WERE FOUND AND SAVED PROPERLY, NOTHING ELSE IN STRING.
                else if (line[*i] == ',' || (found >= 3 && line[*i] != '\0'))
                        return (-1);    //MORE THAN ONE COMMA BETWEEN VALS OR MORE THAN 3 VALS, SO ERROR.
                start = *i;
                while (line[*i] && line[*i] != ',')
                {
                        //TRAILING SPACES ARE ONLY ACCEPTED ON THE LAST NUMBER, NOT ON THE OTHERS.
                        if (found < 2 && (line[*i] < '0' || line[*i] > '9') && line[*i] != '+')
                                return (-1);
                        else if (found == 2 && (line[*i] < '0' || line[*i] > '9')
                                && line[*i] != '+' && line[*i] != ' ' && (line[*i] < 9 || line[*i] > 11))
                                return (-1);
                        (*i)++;
                }
                if (save_cols(data, ft_substr(line, start, *i - start), &found, 2) == -1)
                        return (-1);
                if (line[*i] != '\0')
                        (*i)++;         //SKIPS THE CURRENT ',' AT THE LINE.
        }
        return ((*data)->c = true, 0);
}

int     verify_colors(t_map_data **data, char *line, int *i)
{
        if (line[*i] == 'F')
        {
                (*i)++;
                if ((*data)->f == true || line[*i] == '\0')
                        return (-1);
                while (line[*i] && (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 11)))
                        (*i)++;
                if (obtain_floor_colors(data, line, i) == -1)
                        return (-1);
                return (0);
        }
        else if (line[*i] == 'C')
        {
                (*i)++;
                if ((*data)->c == true || line[*i] == '\0')
                        return (-1);
                while (line[*i] && (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 11)))
                        (*i)++;
                if (obtain_ceiling_colors(data, line, i) == -1)
                        return (-1);
                return (0);
        }
}

int     verify_texture(t_map_data **data, char *line, int *i)
{
        int     start;

        start = 0;
        if (line[*i] == 'N' && line[*i + 1] && line[*i + 1] == 'O')
        {
                *i = *i + 2;
                if ((*data)->no == true || line[*i] == '\0')
                        return (-1);
                while (line[*i] && (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 11)))
                        (*i)++;
                start = *i;
                while (line[*i] && line[*i] != ' ' && (line[*i] < 9 || line[*i] > 11))
                        (*i)++;
                (*data)->map_values->texture_no = ft_substr(line, start, *i - start);
                if (!(*data)->map_values->texture_no)
                        return (-1);
                while (line[*i])
                {
                        if (line[*i] != ' ' && (line[*i] < 9 || line[*i] > 11))
                                return (free((*data)->map_values->texture_no), -1);
                        (*i)++;
                }
                (*data)->no = true;
                //printf("\n\nDEBUG PRINTF, VAL OF TEXTURE_NO: %s\n",(*data)->map_values->texture_no);
                return (0);
        }
        else if (line[*i] == 'S' && line[*i + 1] && line[*i + 1] == 'O')
        {
                *i = *i + 2;
                if ((*data)->so == true || line[*i] == '\0')
                        return (-1);

                while (line[*i] && (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 11)))
                        (*i)++;
                start = *i;
                while (line[*i] && line[*i] != ' ' && (line[*i] < 9 || line[*i] > 11))
                        (*i)++;
                (*data)->map_values->texture_so = ft_substr(line, start, *i - start);
                if (!(*data)->map_values->texture_so)
                        return (-1);
                while (line[*i])
                {
                        if (line[*i] != ' ' && (line[*i] < 9 || line[*i] > 11))
                                return (free((*data)->map_values->texture_so), -1);
                        (*i)++;
                }
                (*data)->so = true;
                //printf("\n\nDEBUG PRINTF, VAL OF TEXTURE_SO: %s\n",(*data)->map_values->texture_so);
                return (0);
        }
        else if (line[*i] == 'E' && line[*i + 1] && line[*i + 1] == 'A')
        {
                *i = *i + 2;
                if ((*data)->ea == true || line[*i] == '\0')
                        return (-1);
                while (line[*i] && (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 11)))
                        (*i)++;
                start = *i;
                while (line[*i] && line[*i] != ' ' && (line[*i] < 9 || line[*i] > 11))
                        (*i)++;
                (*data)->map_values->texture_ea = ft_substr(line, start, *i - start);
                if (!(*data)->map_values->texture_ea)
                        return (-1);
                while (line[*i])
                {
                        if (line[*i] != ' ' && (line[*i] < 9 || line[*i] > 11))
                                return (free((*data)->map_values->texture_ea), -1);
                        (*i)++;
                }
                (*data)->ea = true;
                //printf("\n\nDEBUG PRINTF, VAL OF TEXTURE_EA: %s\n",(*data)->map_values->texture_ea);
                return (0);
        }
        else if (line[*i] == 'W' && line[*i + 1] && line[*i + 1] == 'E')
        {
                *i = *i + 2;
                if ((*data)->we == true || line[*i] == '\0')
                        return (-1);
                while (line[*i] && (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 11)))
                        (*i)++;
                start = *i;
                while (line[*i] && line[*i] != ' ' && (line[*i] < 9 || line[*i] > 11))
                        (*i)++;
                (*data)->map_values->texture_we = ft_substr(line, start, *i - start);
                if (!(*data)->map_values->texture_we)
                        return (-1);
                while (line[*i])
                {
                        if (line[*i] != ' ' && (line[*i] < 9 || line[*i] > 11))
                                return (free((*data)->map_values->texture_we), -1);
                        (*i)++;
                }
                (*data)->we = true;
                //printf("\n\nDEBUG PRINTF, VAL OF TEXTURE_WE: %s\n",(*data)->map_values->texture_we);
                return (0);
        }
        return (-1);
}
