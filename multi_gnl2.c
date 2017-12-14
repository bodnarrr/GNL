/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_gnl2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 16:15:48 by abodnar           #+#    #+#             */
/*   Updated: 2017/12/14 16:15:49 by abodnar          ###   ########.fr       */
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

	while (old && old->fd != fd)
		old = old->next;
	if (old)
	{
		if (ft_find_nl(old->str) == -1)
		{
			*line = ft_strdup(old->str);
			ft_bzero(old->str, BUFF_SIZE);
		}
		else
		{
			*line = ft_strnew(ft_find_nl(old->str));
			ft_memcpy(*line, old->str, ft_find_nl(old->str));
			temp = ft_strdup(old->str + ft_find_nl(old->str) + 1);
			ft_bzero(old->str, BUFF_SIZE);
			ft_memcpy(old->str, temp, ft_strlen(temp));
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
		*line = ft_strnew(ft_strlen(temp) + ft_strlen(buff));
		ft_memcpy(*line, temp, ft_strlen(temp));
		ft_strdel(&temp);
		ft_memcpy(*line + ft_strlen(*line), buff, ft_strlen(buff));
		ft_bzero(buff, BUFF_SIZE);
	}
	else
	{
		*line = ft_strdup(buff);
		ft_bzero(buff, BUFF_SIZE);
	}
}

void	ft_keep_rest(char *buff, t_line **old, int got, int fd)
{
	t_line	*temp;
	t_line	*new;

	if (!*old)
	{
		*old = (t_line*)malloc(sizeof(t_line));
		(*old)->str = ft_strnew(BUFF_SIZE);
		ft_memcpy((*old)->str, buff + got + 1, BUFF_SIZE - got - 1);
		ft_bzero(buff, BUFF_SIZE);
		(*old)->fd = fd;
		(*old)->next = NULL;
	}
	else
	{
		temp = *old;
		while (temp && temp->fd != fd)
			temp = temp->next;
		if (temp)
		{
			ft_memcpy(temp->str, buff + got + 1, BUFF_SIZE - got - 1);
			ft_bzero(buff, BUFF_SIZE);
		}
		else
		{
			new = (t_line*)malloc(sizeof(t_line));
			new->str = ft_strnew(BUFF_SIZE);
			ft_memcpy(new->str, buff + got + 1, BUFF_SIZE - got - 1);
			new->fd = fd;
			new->next = *old;
			*old = new;
		}
	}
}

int		ft_gnl_keep(char *buff, char **line, t_line **old, int got, int fd)
{
	char	*temp;

	if (*line)
	{
		temp = ft_strdup(*line);
		ft_strdel(line);
		*line = ft_strnew(ft_strlen(temp) + got);
		ft_memcpy(*line, temp, ft_strlen(temp));
		ft_strdel(&temp);
		ft_memcpy(*line + ft_strlen(*line), buff, got);
		ft_keep_rest(buff, old, got, fd);
	}
	else
	{
		*line = ft_strnew(got);
		ft_memcpy(*line, buff, got);
		ft_keep_rest(buff, old, got, fd);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static t_line	*old;
	char			*buff;
	int				res;

	t_line *tata = old;
	while (tata)
		tata = tata->next;
	if (fd == -1 || BUFF_SIZE < 1 || !line)
		return (-1);
	if (old && ft_check_old(fd, old, line))
		return (1);
	buff = ft_strnew(BUFF_SIZE);
	while ((res = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (ft_find_nl(buff) == -1)
			ft_add_buff_to_line(buff, line);
		else
			return (ft_gnl_keep(buff, line, &old, ft_find_nl(buff), fd));
	}
	if (res == 0 && (!*line || !**line))
	{
		ft_strdel(line);
		return (0);
	}
	ft_strdel(&buff);
	if (*line && **line)
		return (1);
	return (0);
}