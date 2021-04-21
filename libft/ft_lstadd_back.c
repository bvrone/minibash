/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:16:22 by aglady            #+#    #+#             */
/*   Updated: 2020/11/03 14:20:21 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (new)
	{
		if (!(*lst))
		{
			new->next = *lst;
			*lst = new;
		}
		else
		{
			tmp = *lst;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}
