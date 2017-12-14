/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:18:19 by abodnar           #+#    #+#             */
/*   Updated: 2017/12/14 17:18:20 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

int		main(int ac, char **av)
{
	int		res;
	int		fd;
	int		fd2;
	char	*line;
	char	*line2;

	if (ac < 2)
	{
		printf("Pass agruments, please.\n");
		return (1);
	}

	fd = open(av[1], O_RDONLY);
	fd2 = open(av[2], O_RDONLY);
	
	while((res = get_next_line(fd, &line)) > 0)
		printf("==line in main = %s\nres = %i\n", line, res);
	printf("==last line in main = %s\nres = %i\n", line, res);

	while((res = get_next_line(fd2, &line2)) > 0)
		printf("==line in main = %s\nres = %i\n", line2, res);
	printf("==last line in main = %s\nres = %i\n", line2, res);

	if ((close(fd)) == -1 || (close(fd2)) == -1)
		return (1);
	return (0);
}