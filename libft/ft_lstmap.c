/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abodnar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:53:06 by abodnar           #+#    #+#             */
/*   Updated: 2017/11/07 18:11:56 by abodnar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*res;
	t_list	*temp;

	if (!lst || !f)
		return (NULL);
	if (!(temp = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	temp = f(lst);
	res = ft_lstnew(temp->content, temp->content_size);
	if (lst->next)
		res->next = ft_lstmap(lst->next, f);
	return (res);
}
