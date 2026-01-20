#include "cub3d.h"

int     atoi_v2(char *str, int *num)
{
        int     i;

        i = 0;
        if (!str)
                return (-1);
        if (str[i] == '+')
                i++;
        if (str[i] < '0' || str[i] > '9')
                return (-1);
        while (str[i] >= '0' && str[i] <= '9' && str[i])
                *num = (*num * 10) + (str[i++] - '0');
        while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 11)))
                i++;
        if (str[i] != '\0')
                return (-1);
        if (*num > 255)
                return (-1);
        return (0);
}

int     get_array_len(char **array)
{
        int     len;

        len = 0;
        if (!array || !array[0])
                return (0);
        while (array[len])
                len++;
        return (len);
}
