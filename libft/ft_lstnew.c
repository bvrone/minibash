/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:30:02 by aglady            #+#    #+#             */
/*   Updated: 2020/11/03 18:46:59 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *data)
{
	t_list	*new_elem;

	new_elem = (t_list *)malloc(sizeof(*new_elem));
	if (new_elem)
	{
		new_elem->data = data;
		new_elem->next = NULL;
	}
	return (new_elem);
}
