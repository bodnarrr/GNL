/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gnl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 10:58:04 by abodnar           #+#    #+#             */
/*   Updated: 2017/12/12 17:03:06 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

int		ft_find_nl(char *str)
{
	int	res;

	res = 0;
	while (*str)
	{
		if (*str == '\n')
			return (res);
		res++;
		str++;
	}
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	static char	*buff;
	char		*temp;
	int			got;

	if (fd == -1)
		return (-1);

	if (buff)
	{
		//printf("FIND OLD BUFF. There is:\n%s\n", buff);
		got = ft_find_nl(buff);
		if (got != -1)
		{
			// printf("Found '/n' in buff!\n");
			// printf("Let's copy %i symbols from buff\n", got);
			*line = ft_strnew(got);
			*line = ft_memcpy(*line, buff, got);
			// printf("Copied line is:\n%s\n", *line);
			// printf("Let's leave %lu symbols in buff\n", ft_strlen(buff) - got - 1);
			temp = ft_strsub(buff, got + 1, ft_strlen(buff) - got - 1);
			ft_bzero(buff, BUFF_SIZE);
			buff = ft_memcpy(buff, temp, ft_strlen(temp));
			ft_strdel(&temp);
			return (1);
		}
		else
		{
			// printf("Not found '/n' in buff!\n");
			*line = ft_strdup(buff);
			ft_bzero(buff, BUFF_SIZE);
		}
	}
	else
	{
		// printf("DIDN'T FIND OLD BUFF, allocate memory new buff\n");
		buff = ft_strnew(BUFF_SIZE);
	}
	while (read(fd, buff, BUFF_SIZE) > 0)
	{
		// printf("Start reading from file\n");
		// printf("What was read:\n%s\n", buff);
		got = ft_find_nl(buff);
		if (got != -1)
		{
			// printf("Found '/n' in buff after reading!\n");
			if (*line)
			{
				// printf("And there is something in *line:\n%s\n", *line);
				// printf("We will copy %i symbols from read buff\n", got);
				temp = ft_strdup(*line);
				ft_strdel(line);
				*line = ft_strnew(ft_strlen(temp) + got);
				*line = ft_strncpy(*line, temp, ft_strlen(temp));
				ft_strdel(&temp);
				*line = ft_strncat(*line, buff, got);
				// printf("Temp will get %lu symbols from buff\n", ft_strlen(buff) - got - 1);
				temp = ft_strsub(buff, got + 1, ft_strlen(buff) - got - 1);
				ft_bzero(buff, BUFF_SIZE);
				buff = ft_memcpy(buff, temp, ft_strlen(temp));
				ft_strdel(&temp);
				// printf("What remaining in buff:\n%s\n", buff);
				// printf("ARE WE HERE?\n");
				return (1);
			}
			else
			{
				// printf("There wasn't *line when we read\n");
				// printf("We will copy %i symbols from read buff\n", got);
				*line = ft_strnew(got);
				*line = ft_memcpy(*line, buff, got);
				// printf("Temp will get %lu symbols from buff\n", ft_strlen(buff) - got - 1);
				temp = ft_strsub(buff, got + 1, ft_strlen(buff) - got - 1);
				ft_bzero(buff, BUFF_SIZE);
				buff = ft_memcpy(buff, temp, ft_strlen(temp));
				ft_strdel(&temp);
				return (1);
			}

		}
		else
		{
			// printf("NO '/n' in buff after reading!\n");
			if (*line)
			{
				temp = ft_strdup(*line);
				ft_strdel(line);
				*line = ft_strjoin(temp, buff);
				ft_bzero(buff, BUFF_SIZE);
			}
			else
			{
				*line = ft_strdup(buff);
				ft_bzero(buff, BUFF_SIZE);
			}
		}
	}

	return (0);
}

int		main(int ac, char **av)
{
	int		fd;
	int		res;
	char	*line;

	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	int i = 0;
	res = get_next_line(fd, &line);
	 printf("line[%i] =\t%s\n", i, line);
	i++;
	//printf("=====FLIN IN MAIN=====\n%s\n======================\nres = %i\n======================\n", line, res);
	while (res > 0)
	{
		res = get_next_line(fd, &line);
		printf("line[%i] =\t%s\n", i, line);
		free(line);
		i++;
		//printf("=====LINE IN MAIN=====\n%s\n======================\nres = %i\n======================\n", line, res);
	}
	//res = get_next_line(fd, &line);
	//printf("=====LAST IN MAIN=====\n%s\n======================\nres = %i\n======================\n", line, res);
	//free(line);
	close (fd);
}
