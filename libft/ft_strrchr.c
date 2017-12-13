/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:04:24 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/07 18:19:38 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = (char*)s;
	while (*s)
		s++;
	while (s >= tmp)
	{
		if (*s == c)
			return ((char*)s);
		s--;
	}
	return (NULL);
}
