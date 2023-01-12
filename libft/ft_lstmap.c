/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkarosas < jkarosas@student.42wolfsburg.de +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:45:28 by jkarosas          #+#    #+#             */
/*   Updated: 2021/12/01 11:51:35 by jkarosas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*a;
	t_list	*b;

	if (lst == NULL)
		return (NULL);
	a = NULL;
	b = NULL;
	while (lst)
	{
		b = ft_lstnew((*f)(lst->content));
		if (b == NULL)
		{
			ft_lstclear(&a, del);
			return (b);
		}
		ft_lstadd_back(&a, b);
		lst = lst->next;
	}
	return (a);
}
