/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strgsort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 11:09:54 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/10 14:07:16 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strgsort(char ***list)
{
	size_t	i;
	size_t	size;

	if (list == NULL || *list == NULL)
		return ;
	while (list[size])
		size++;
	i = 1;
	while (i < size)
	{
		if (i == 0 || ft_strcmp(*list[i - 1], *list[i]) <= 0)
			i++;
		else
		{
			ft_strswap(&*(list[i - 1]), &(*list[i]));
			i--;
		}
	}
}
