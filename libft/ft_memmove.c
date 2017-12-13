/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:53:25 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/07 18:14:12 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst1;
	unsigned char	*src1;
	int				flag;

	dst1 = (unsigned char*)dst;
	src1 = (unsigned char*)src;
	i = 0;
	flag = 0;
	while (i < len)
		if (dst1 == src1 + i++)
			flag = 1;
	if (flag)
	{
		i = len - 1;
		while (len)
		{
			*(dst1 + i) = *(src1 + i);
			len--;
			i--;
		}
	}
	else
		dst = ft_memcpy(dst, src, len);
	return (dst);
}
