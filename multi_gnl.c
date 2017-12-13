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

	while (old && old->fd != fd)
		old = old->next;
	if (old)
	{
		printf("Found list element with fd!\n");
		printf("This buff keeps:\n%s\n", old->str);
		got = ft_find_nl(old->str);
		if (got == -1)
		{
			printf("No '/n' fot this fd\n");
			*line = ft_strdup(old->str);
			ft_bzero(old->str, BUFF_SIZE);
		}
		else
		{
			printf("Found '/n' fot this fd\n");
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

	temp = ft_strdup(*line);
	ft_strdel(line);
	*line = ft_strjoin(temp, buff);
	ft_bzero(buff, BUFF_SIZE);

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
		printf("Read buffer is:%s\n", buff);
		got = ft_find_nl(buff);
		if (got == -1)
			ft_add_buff_to_line(buff, line);
	}

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
	while (res > 0)
	{
		res = get_next_line(fd, &line);
		printf("line[%i] =\t%s\n", i, line);
		free(line);
		i++;	
	}
	close (fd);
}