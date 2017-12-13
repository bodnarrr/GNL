/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:32:01 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/07 18:11:24 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*fordel;

	if (!alst || !del || !*alst)
		return ;
	while (*alst)
	{
		del((*alst)->content, (*alst)->content_size);
		fordel = *alst;
		*alst = (*alst)->next;
		free(fordel);
	}
	*alst = NULL;
}
