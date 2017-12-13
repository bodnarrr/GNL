/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gnl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 10:58:04 by abodnar           #+#    #+#             */
/*   Updated: 2017/12/08 10:58:05 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

//Func take char *temp, **list and fd, check if there if fd and add from temp to (*list)->str


static int	ft_find_nl(char *str)	//find '\n' in str ret (-1) if there isn't
{
	int		res;

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

static int	ft_find_in_list(t_line *list, int fd, char **line)
{
	char	*temp;

	while (list)
	{
		if (list->fd == fd)
		{
			printf("Found list's element with needle fd\n");
			
			if (ft_find_nl(list->str) == -1)
			{
				printf("Not found '/n' in elem->str\n");
				*line = ft_strdup(list->str);
				ft_bzero(list->str, BUFF_SIZE);
				return (0);
			}
			else
			{
				printf("Found '/n' in elem->str\n");
				printf("Let's copy %i symbols from this str\n", ft_find_nl(list->str));
				*line = ft_strnew(ft_find_nl(list->str));
				*line = ft_memcpy(*line, list->str, ft_find_nl(list->str));
				printf("Copied *line is:\n%s\n", *line);
				temp = ft_strdup(line->str + ft_find_nl(list->str) + 1);
				ft_bzero(list->str, BUFF_SIZE);
				list->str = ft_memcpy(list->str, temp, BUFF_SIZE - ft_find_nl(list->str) - 1);
				ft_strdel(&temp);
				printf("Check what remains in element's str:\n%s\n", list->str);
				return (1);
			}
		}
		list = list->next;
	}
	return (0);
}

void	ft_save_list(char *buff, char **line, t_line **list, int cpy, int fd)
{
	char	*tempstr;
	t_line	*templist;

	if (!*line)
	{
		*line = ft_strnew(cpy);
		*line = ft_memcpy(*line, buff, cpy);
		if (!*list)
		{
			*list = (t_line*)malloc(sizeof(t_line));
			(*list)->str = ft_strnew(BUFF_SIZE);
			ft_memcpy((*list)->str, buff + cpy + 1, BUFF_SIZE - cpy - 1);
		}
		else
		{
			templist = *list;
			while (templist)
			{
				if (templist->fd == fd)
					ft_memcpy(templist->str, buff + cpy + 1, BUFF_SIZE - cpy - 1);
				templist = templist->next;
			}
			if (!templist)
			{

			}
		}
	}
}

int		get_next_line(int fd, char **line)
{
	static t_line	*list;
	char			*buff;
	char			*temp;

	if (fd == -1)
		return (-1);
	
	if (list)
	{
		if (ft_find_in_list(list, fd, line) == 1)
		{
			printf("Found '/n' in list for this fd. GNL stops here.\n");
			printf("Written line:\n%s\n", *line);
			return (1);
		}
	}
	
	printf("Checked old list\n");
	if (*line)
		printf("There wasn't '/n'. Line after checking:\n%s\n", *line);

	buff = ft_strnew(BUFF_SIZE);

	while (read(fd, buff, BUFF_SIZE) > 0)
	{
		printf("Start reading from file.\nRead buffer:\n%s\n", buff);
		if (ft_find_nl(buff) == -1)
		{
			printf("Not found '/n' in read buffer\n");
			printf("Read buffer is:\n%s\n", buff);
			if (*line)
			{
				printf("And line isn't empty:\n%s\n", *line);
				temp = ft_strdup(*line);
				ft_strdel(*line);
				*line = ft_strjoin(temp, buff);
				ft_strdel(&temp);
				ft_bzero(buff);
			}
			else
			{
				printf("And line is empty.\n", *line);
				*line = ft_strdup(buff);
				ft_bzero(buff);
			}
		}
		else
		{
			ft_save_list(buff, line, &list, ft_find_nl(buff), fd);
			ft_strdel(&buff);
			return (1);
		}
	}
	return (9);
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
	// printf("=====FLIN IN MAIN=====\n%s\n======================\nres = %i\n======================\n", line, res);
	while (res > 0)
	{
		res = get_next_line(fd, &line);
		printf("line[%i] =\t%s\n", i, line);
		free(line);
		i++;
		// printf("=====LINE IN MAIN=====\n%s\n======================\nres = %i\n======================\n", line, res);
	}
	res = get_next_line(fd, &line);
	// printf("=====LAST IN MAIN=====\n%s\n======================\nres = %i\n======================\n", line, res);
	free(line);
	close (fd);
}