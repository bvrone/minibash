/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:44:38 by aglady            #+#    #+#             */
/*   Updated: 2020/11/03 19:02:21 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*tmp;

	res = NULL;
	if (lst && f)
	{
		res = ft_lstnew((*f)(lst->data));
		if (res)
		{
			lst = lst->next;
			tmp = res;
			while (lst)
			{
				tmp->next = ft_lstnew((*f)(lst->data));
				lst = lst->next;
				tmp = tmp->next;
				if (!tmp)
				{
					ft_lstclear(&res, del);
					return (NULL);
				}
			}
		}
	}
	return (res);
}
