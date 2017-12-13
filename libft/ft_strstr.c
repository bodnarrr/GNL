/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 18:09:55 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/07 18:20:00 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;

	if (!*needle)
		return ((char*)haystack);
	while (*haystack)
	{
		i = 0;
		while (*(haystack + i) == needle[i] && *(haystack + i))
			i++;
		if (needle[i] == '\0')
			return ((char*)haystack);
		haystack++;
	}
	return (NULL);
}
