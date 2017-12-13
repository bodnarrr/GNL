/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:51:40 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/07 18:18:20 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	result;
	size_t	max_write;

	result = ((dstsize < ft_strlen(dst)) ? (ft_strlen(src) + dstsize) :
			(ft_strlen(dst) + ft_strlen(src)));
	if (!dstsize)
		return (result);
	if ((max_write = dstsize - ft_strlen(dst) - 1) < 1
			|| (dstsize < ft_strlen(dst) + 1))
		return (result);
	while (*dst)
		dst++;
	while (max_write && *src)
	{
		*dst++ = *src++;
		max_write--;
	}
	*dst = '\0';
	return (result);
}
