/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:38:38 by aglady            #+#    #+#             */
/*   Updated: 2020/11/03 15:01:42 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	len;

	len = count * size;
	res = malloc(len);
	if (res)
	{
		while (len)
		{
			len--;
			((unsigned char *)res)[len] = '\0';
		}
	}
	return (res);
}
