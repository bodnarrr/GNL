/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 19:51:48 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/07 18:15:38 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_sqrt(int nb)
{
	int min;
	int max;
	int middle;

	min = 0;
	max = 46340;
	while (min <= max)
	{
		middle = (min + max) / 2;
		if ((middle * middle) == nb)
			return (middle);
		else if ((middle * middle) > nb)
			max = middle - 1;
		else
			min = middle + 1;
	}
	return (0);
}
