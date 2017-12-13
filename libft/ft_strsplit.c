/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:01:22 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/10 13:47:41 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *str, char delim)
{
	int		i;
	int		size;
	int		counter;
	int		flag;

	if (str == NULL)
		return (-1);
	i = 0;
	flag = 0;
	counter = 0;
	size = ft_strlen(str);
	while (i < size)
	{
		if (str[i] == delim)
			flag = 0;
		else if (str[i] != delim && flag == 0)
		{
			flag = 1;
			counter++;
		}
		i++;
	}
	return (counter);
}

static char	*ft_save_words(char const *str, char delim)
{
	int		i;
	char	*word;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != delim)
		i++;
	word = (char*)malloc(sizeof(char) * (i + 1));
	if (word == NULL)
		return (NULL);
	i = -1;
	while (str[++i] != delim)
		word[i] = str[i];
	word[i] = '\0';
	return (word);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**res;
	int		words;
	int		i;

	if (s == NULL)
		return (NULL);
	words = ft_word_count(s, c);
	if (!(res = (char**)malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		res[i++] = ft_save_words(s, c);
		while (*s != c && *s)
			s++;
	}
	res[i] = NULL;
	return (res);
}
