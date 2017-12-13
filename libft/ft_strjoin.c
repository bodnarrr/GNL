/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:27:09 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/07 18:18:08 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	res = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (*s1)
	{
		*(res + i) = *s1++;
		i++;
	}
	while (*s2)
	{
		*(res + i) = *s2++;
		i++;
	}
	*(res + i) = '\0';
	return (res);
}
