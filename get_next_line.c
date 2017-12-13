/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:29:15 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/27 13:29:16 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

void	ft_realloc(char **str, char *buff)
{
	char	*temp;

	printf("sizeof str = %zu\n", sizeof(*str));
	temp = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	temp = (char*)ft_memcpy(temp, *str, BUFF_SIZE + 1);
	free(*str);
	*str = (char*)malloc(sizeof(char) * (2 * BUFF_SIZE + 1));
	int i = 0;
	while (temp[i])
	{
		(*str)[i] = temp[i];
		i++;
	}
	*str = ft_strncat(*str, buff, BUFF_SIZE);
	printf("finish = %s\n", *str);
	printf("sizeof str = %zu\n", sizeof(*str));
	free(temp);
}

int		get_next_line(const int fd, char **line)
{
	char	buff[BUFF_SIZE];
	int		i;

	if (fd == -1)
		return (-1);
	if (read (fd, buff, BUFF_SIZE) == -1)
		return (-1);
	*line = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	i = 0;
	while (i < BUFF_SIZE)
	{
		(*line)[i] = buff[i];
		i++;
	}
	(*line)[i] = '\0';
	printf("line = %s\n", *line);
	if (read (fd, buff, BUFF_SIZE) == -1)
		return (-1);
	ft_realloc(line, buff);


	return (1);
}

int		main(int ac, char **av)
{
	int		fd;
	char	*str;
	int		testing;
	
	if (ac != 2)
		return (1);
	fd = open (av[1], O_RDONLY);
	testing = get_next_line(fd, &str);
	printf("str = %s\ntesting = %i\n", str, testing);
}