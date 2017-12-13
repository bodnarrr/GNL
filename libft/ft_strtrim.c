/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:44:51 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/07 18:20:30 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

char		*ft_strtrim(char const *s)
{
	size_t	white_e;
	size_t	size;
	char	*res;

	if (s == NULL)
		return (NULL);
	while (ft_isspace(*s) == 1 && *s)
		s++;
	size = ft_strlen(s);
	if (size == 0)
		return (res = ft_strnew(size));
	white_e = 0;
	while (ft_isspace(s[size - 1]) == 1)
	{
		white_e++;
		size--;
	}
	res = ft_strsub(s, 0, ft_strlen(s) - white_e);
	return (res);
}
