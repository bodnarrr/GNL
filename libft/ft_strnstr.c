/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:24:10 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/07 18:19:30 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	int		i;
	size_t	temp;

	if (!*little)
		return ((char*)big);
	while (*big && n)
	{
		i = 0;
		temp = n;
		while (*(big + i) == little[i] && *(big + i) && temp)
		{
			i++;
			temp--;
		}
		if (little[i] == '\0')
			return ((char*)big);
		big++;
		n--;
	}
	return (NULL);
}
