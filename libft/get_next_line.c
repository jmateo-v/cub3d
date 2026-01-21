/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrlinei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 04:53:44 by adrlinei          #+#    #+#             */
/*   Updated: 2024/03/27 05:14:37 by adrlinei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*substring(char *src, int begin, int end)
{
	char	*dst;
	int		i;

	i = 0;
	if (!src || !end)
		return (stringdup(""));
	if (end > (len_str(src) - begin))
		end = len_str(src) - begin;
	dst = (char *)malloc((len_str(src) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while ((end > 0) && (src[begin]))
	{
		dst[i] = src[begin];
		i++;
		begin++;
		end--;
	}
	dst[i] = '\0';
	return (dst);
}

char	*stringjoin(char *s1, char *s2)
{
	char	*dst;
	int		i;
	int		j;

	if (!s1)
		return (stringdup(s2));
	if (!s2)
		return (stringdup(s1));
	i = 0;
	j = 0;
	dst = (char *)malloc((len_str(s1) + len_str(s2) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
		dst[i++] = s2[j++];
	dst[i] = '\0';
	return (free(s1), dst);
}

char	*r_line(char *stash, int fd)
{
	char	*buffer;
	int		bytes_r;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_r = 1;
	while ((check_nl(stash) <= 0) && bytes_r)
	{
		bytes_r = read(fd, buffer, BUFFER_SIZE);
		if (bytes_r == 0)
		{
			if (stash)
				return (free(buffer), stash);
			return (free(buffer), free(stash), NULL);
		}
		if (bytes_r <= -1)
			return (free(buffer), free(stash), NULL);
		buffer[bytes_r] = '\0';
		stash = stringjoin(stash, buffer);
		if (!stash)
			return (free(buffer), NULL);
	}
	return (free(buffer), stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*tmp;

	line = NULL;
	tmp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = r_line(stash, fd);
	if (!stash)
		return (NULL);
	line = substring(stash, 0, (get_nl(stash) + 1));
	if (!line || !line[0])
		return (free(line), free(stash), NULL);
	tmp = substring(stash, (get_nl(stash) + 1), len_str(stash));
	free(stash);
	stash = NULL;
	if (!tmp || !tmp[0])
	{
		if (line)
			return (free(tmp), line);
		return (free(tmp), NULL);
	}
	stash = stringdup(tmp);
	return (free(tmp), line);
}

/*int	main(void)
{
	char	*line;
	int	fd = open("alternate_line_nl_no_nl",O_RDONLY);
	int	limit;
	
	limit = 0;
	if (fd == -1)
	{
		printf("\ninvalid fd\n");
		return (0);
	}
	printf("\nfile open success\n"); 
	while (limit < 15)
	{
		printf("\ncall to gnl\n");
		line = get_next_line(fd);
		if (!line)
		{
			printf("\nerror reading line\n");
			return (0);
		}
		printf("line: \n'%s'\n",line);
		free(line);
		limit++;
	}
	close(fd);
}*/
