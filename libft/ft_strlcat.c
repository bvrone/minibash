/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:49:50 by aglady            #+#    #+#             */
/*   Updated: 2020/11/03 15:14:16 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (dstsize > 0)
	{
		while (dst[i] && i < dstsize - 1)
			i++;
		if (i < dstsize - 1)
		{
			while (src[j] && i < dstsize - 1)
			{
				dst[i] = src[j];
				i++;
				j++;
			}
			dst[i] = '\0';
		}
	}
	if (ft_strlen(dst) < dstsize)
		return (ft_strlen(dst) + ft_strlen(src));
	else
		return (dstsize + ft_strlen(src));
}

void	ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	len;

	if (!src)
		return ;
	i = 0;
	len = ft_strlen(dst);
	while (src[i])
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
}
