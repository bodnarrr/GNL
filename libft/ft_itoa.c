/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:01:45 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/07 18:11:06 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_input_size(int n)
{
	int		counter;

	counter = ((n < 0) ? 2 : 1);
	while (n /= 10)
		counter++;
	return (counter);
}

static void	ft_reverse_str(char *str)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

char		*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		size;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = ft_input_size(n);
	if (!(res = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		*(res + size - 1) = '-';
	}
	i = -1;
	while (i++ < size)
	{
		if (*(res + size - 1) == '-' && i == size - 1)
			break ;
		res[i] = n % 10 + '0';
		n /= 10;
	}
	*(res + size) = '\0';
	ft_reverse_str(res);
	return (res);
}
