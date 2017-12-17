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

#include "get_next_line.h"

int		main(int ac, char **av)
{
	int		res;
	int		fd;
	char	*line;

	if (ac < 2)
	{
		printf("Pass agruments, please.\n");
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	while((res = get_next_line(fd, &line)) > 0)
		printf("==line in main = %s\nres = %i\n", line, res);
	free(line);
	if ((close(fd)) == -1)
		return (1);
	return (0);
}