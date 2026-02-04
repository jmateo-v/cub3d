/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrlinei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:36:44 by adrlinei          #+#    #+#             */
/*   Updated: 2026/02/04 20:36:46 by adrlinei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	alt_atoi(char *str, int *num)
{
	int	i;

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

char	*alt_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	dst = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!dst)
		return (NULL);
	while (s1[++i])
		dst[i] = s1[i];
	while (s2[j])
	{
		dst[i] = s2[j];
		i++;
		j++;
	}
	free((char *)s1);
	return (dst);
}

int	get_array_len(char **array)
{
	int	len;

	len = 0;
	if (!array || !array[0])
		return (0);
	while (array[len])
		len++;
	return (len);
}
