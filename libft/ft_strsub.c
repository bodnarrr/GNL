/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:18:40 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/07 18:20:08 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	if (s == NULL)
		return (NULL);
	res = ft_strnew(len);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (len)
	{
		*(res + i) = *(s + start);
		start++;
		i++;
		len--;
	}
	*(res + i) = '\0';
	return (res);
}
