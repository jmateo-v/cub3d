/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrlinei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 04:52:43 by adrlinei          #+#    #+#             */
/*   Updated: 2024/03/27 04:53:01 by adrlinei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*r_line(char *stash, int fd);
char	*substring(char *src, int begin, int end);
char	*stringdup(char *src);
char	*stringjoin(char *s1, char *s2);
int		check_nl(char *str);
int		len_str(char *str);
int		get_nl(char *str);

#endif
