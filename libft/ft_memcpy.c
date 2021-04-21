/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:23:14 by aglady            #+#    #+#             */
/*   Updated: 2020/11/03 15:05:25 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t count)
{
	size_t	i;

	if (dest != (char *)source)
	{
		i = 0;
		while (i < count)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)source)[i];
			i++;
		}
	}
	return (dest);
}
