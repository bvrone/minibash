/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:31:36 by aglady            #+#    #+#             */
/*   Updated: 2020/11/03 15:06:08 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *source, size_t count)
{
	size_t	i;

	if (dest < source)
	{
		i = 0;
		while (i < count)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)source)[i];
			i++;
		}
	}
	if (dest > source)
	{
		i = count;
		while (i > 0)
		{
			i--;
			((unsigned char *)dest)[i] = ((unsigned char *)source)[i];
		}
	}
	return (dest);
}
