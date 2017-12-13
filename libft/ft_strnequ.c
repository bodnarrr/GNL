/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:06:00 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/10 14:02:24 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t len)
{
	size_t i;

	if (len == 0)
		return (1);
	if (s1 == NULL || s2 == NULL)
		return (-1);
	i = 0;
	while (*(s1 + i) == *(s2 + i) && s1 && s2 && (len - 1))
	{
		i++;
		len--;
	}
	return (((unsigned char)s1[i] == (unsigned char)s2[i]) ? 1 : 0);
}
