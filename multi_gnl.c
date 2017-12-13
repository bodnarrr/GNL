/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:21:28 by abodnar           #+#    #+#             */
/*   Updated: 2017/12/13 15:21:29 by abodnar          ###   ########.fr       */
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

int		ft_check_old(int fd, t_line *old, char **line)
{
	char	*temp;
	int		got;

	printf("Check fd in first elem: %i\n", old->fd);
	printf("Check buff in list:\n=======================\n%s\n=======================\n", old->str);
	while (old && old->fd != fd)
		old = old->next;
	if (old)
	{
		got = ft_find_nl(old->str);
		if (got == -1)
		{
			*line = ft_strdup(old->str);
			ft_bzero(old->str, BUFF_SIZE);
		}
		else
		{
			*line = ft_strnew(got);
			*line = ft_memcpy(*line, old->str, got);
			temp = ft_strsub(old->str, got + 1, ft_strlen(old->str) - got - 1);
			ft_bzero(old->str, BUFF_SIZE);
			old->str = ft_memcpy(old->str, temp, ft_strlen(temp));
			ft_strdel(&temp);
			return (1);
		}
	}
	return (0);
}

void	ft_add_buff_to_line(char *buff, char **line)
{
	char	*temp;

	if (*line)
	{
		temp = ft_strdup(*line);
		ft_strdel(line);
		*line = ft_strjoin(temp, buff);
		ft_bzero(buff, BUFF_SIZE);
	}
	*line = ft_strdup(buff);
	ft_bzero(buff, BUFF_SIZE);
}

void	ft_keep_rest(char *buff, t_line **old, int got, int fd)
{
	t_line	*temp;
	t_line	*new;

	if (!*old)
	{
		*old = (t_line*)malloc(sizeof(t_line));
		(*old)->str = ft_strnew(BUFF_SIZE);
		printf("Check what will be saved:\n%s\n", buff + got + 1);
		ft_memcpy((*old)->str, buff + got + 1, ft_strlen(buff) - got - 1);
		(*old)->fd = fd;
	}
	else
	{
		temp = *old;
		while (temp && temp->fd != fd)
			temp = temp->next;
		if (!temp)
		{
			new = (t_line*)malloc(sizeof(t_line));
			new->str = ft_strnew(BUFF_SIZE);
			new->str = ft_memcpy(new->str, buff + got + 1, ft_strlen(buff) - got - 1);
			new->fd = fd;
			new->next = *old;
			*old = new;
		}
		temp->str = ft_memcpy(temp->str, buff + got + 1, ft_strlen(buff) - got - 1);
		temp->fd = fd;
	}
}

void	ft_gnl(char *buff, char **line, t_line **old, int got, int fd)
{
	char	*temp;

	printf("Found '/n' in read buffer\n");
	if (*line)
	{
		temp = ft_strdup(*line);
		ft_strdel(line);
		*line = ft_strnew(ft_strlen(temp) + got);
		*line = ft_memcpy(*line, temp, ft_strlen(temp));
		*line = ft_strncat(*line, buff, got);
		ft_keep_rest(buff, old, got, fd);
	}
	else
	{
		printf("There wasn't line at the start\n");
		*line = ft_strnew(got);
		*line = ft_memcpy(*line, buff, got);
		ft_keep_rest(buff, old, got, fd);
	}
}

int		get_next_line(int fd, char **line)
{
	static t_line	*old;
	char			*buff;
	int				got;
	
	if (fd == -1 || BUFF_SIZE < 1 || !line)
	{
		printf("Something is wrong with you!\n");
		return (-1);
	}

	printf("------------------START GNL ------------------\n");
	if (old != NULL)
	{
		printf("Found list with old info\n");
		if (ft_check_old(fd, old, line) == 1)
		{
			printf("Line was in list.\n");
			return (1);
		}
	}
	buff = ft_strnew(BUFF_SIZE);
	printf("Start reading from file\n");
	while (read(fd, buff, BUFF_SIZE) > 0)
	{
		printf("Read buffer is:\n%s\n", buff);
		got = ft_find_nl(buff);
		if (got == -1)
			ft_add_buff_to_line(buff, line);
		else
		{
			ft_gnl(buff, line, &old, got, fd);
			return (1);
		}
	}
	ft_strdel(&buff);
	return (0);
}

int		main(int ac, char **av)
{
	int		fd;
	int		res;
	char	*line;

	if (ac > 3)
		return (1);
	fd = open(av[1], O_RDONLY);
	int i = 1;
	res = get_next_line(fd, &line);
	 printf("line[%i] =\t%s\n", i, line);
	i++;
	while (res > 0)
	{
		res = get_next_line(fd, &line);
		printf("line[%i] =\t%s\n", i, line);
		free(line);
		i++;	
	}
	close (fd);
}