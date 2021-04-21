/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:56:23 by aglady            #+#    #+#             */
/*   Updated: 2020/11/03 15:11:26 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*res;

	if (!s)
		return (NULL);
	res = (char *)s;
	while (*res)
	{
		if ((unsigned char)*res == (unsigned char)c)
			return (res);
		res++;
	}
	if ((unsigned char)*res == (unsigned char)c)
		return (res);
	return (NULL);
}
