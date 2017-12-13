/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get6.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:35:52 by abodnar           #+#    #+#             */
/*   Updated: 2017/12/06 16:35:54 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

int		get_next_line(int fd, char **line)
{
	static char	*buff;
	char		*temp;
	long int	found_n;

	if (fd == -1)
		return (-1);
	
	printf("----Starting GNL func----\n");


	if (buff)
	{
		printf("There is something in old buffer before new reading\n");
		found_n = ft_strchr(buff, '\n') - buff;
		printf("Found_n = %li\n", found_n);

		if (found_n >= 0 && found_n <= (long int)ft_strlen(buff))
		{
			printf("'/n' was found in old buffer\n");

			*line = ft_strsub(buff, 0, found_n);
			printf("written line is\n%s\n", *line);
			temp = ft_strdup(buff);
			ft_strdel(&buff);
			buff = ft_strsub(temp, found_n + 1, (long int)ft_strlen(temp) - found_n - 1);
			printf("remaining in buff is\n%s\n", buff);
			ft_strdel(&temp);
			return (1);
		}
		else
		{
			printf("NO '/n' was found in old buffer\n");
			*line = ft_strdup(buff);
			ft_bzero(buff, BUFF_SIZE);
			printf("Line after taking inf from buff is\n%s\n", *line);
		}
	}
	else
	{
		printf("Buffer was empty when GNL started\n");
		buff = ft_strnew(BUFF_SIZE);
		ft_bzero(buff, BUFF_SIZE);
	}

	while (read(fd, buff, BUFF_SIZE) > 0)
	{
		 printf("Readind started. What was read?\n%s\n", buff);
		 found_n = ft_strchr(buff, '\n') - buff;

		 if(found_n >= 0 && found_n <= (long int) ft_strlen(buff))
		 {
		 	printf("'/n' was found in read buffer\n");

		 	if(*line)
		  	{
		 		printf("And something was in line\n");

		 		temp = ft_strdup(*line);
		 		ft_strdel(line);
		 		*line = ft_strnew(ft_strlen(temp) + found_n);
		 		*line = ft_strncat(*line, temp, ft_strlen(temp));
		 		ft_strdel(&temp);
		 		*line = ft_strncat(*line, buff, found_n);
		 		printf("WTF = %li\n", ft_strlen(buff) - found_n - 1);
		 		temp = ft_strnew(ft_strlen(buff) - found_n - 1);
		 		temp = ft_strsub(buff, found_n + 1, ft_strlen(buff) - found_n - 1);
		 		ft_strdel(&buff);
		 		buff = ft_strdup(temp);
		 		ft_strdel(&temp);
		 		printf("Check what remaining if buffer\n%s\n", buff);
		 		return (1);
		 	}
		 	else
		 	{
		 		printf("And nothing was in line\n");
		 		*line = ft_strnew(found_n);
		 		*line = ft_strncat(*line, buff, found_n);
		 		printf("WTF = %li\n", ft_strlen(buff) - found_n - 1);
		 		temp = ft_strnew(ft_strlen(buff) - found_n - 1);
		 		temp = ft_strsub(buff, found_n + 1, ft_strlen(buff) - found_n - 1);
		 		ft_strdel(&buff);
		 		buff = ft_strdup(temp);
		 		ft_strdel(&temp);
		 		printf("Check what remaining if buffer\n%s\n", buff);
		 		return (1);
		 	}
		}
		 else
		 {
		 	printf("NO '/n' was found in read buffer\n");

		 	if (*line)
		 	{
		 		printf("And something was in line\n");
		 		temp = ft_strdup(*line);
		 		ft_strdel(line);
		 		*line = ft_strnew(ft_strlen(temp) + ft_strlen(buff));
		 		*line = ft_strjoin(temp, buff);
		 		ft_strdel(&temp);
		 		ft_bzero(buff, BUFF_SIZE);
		 	}
		 	else
		 	{
		 		printf("And nothing was in line\n");
		 		*line = ft_strdup(buff);
		 		ft_bzero(buff, BUFF_SIZE);
		 	}
		 }
	}
	return (0);
}

int			main(int ac, char **av)
{
	int		fd;
	char	*str;

	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &str))
	{
		printf("=====READ LINE=====\n%s\n===================\n", str);
		free(str);
	}
	printf("====LAST LINE====\n%s\n===================\n", str);
	free(str);

	return (0);
}