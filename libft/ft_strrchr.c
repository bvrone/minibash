/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 22:31:13 by aglady            #+#    #+#             */
/*   Updated: 2020/11/03 15:18:38 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	size_t	len;
	char	*res;

	len = ft_strlen(str);
	res = (char *)(str + len);
	if ((unsigned char)ch == '\0')
		return (res);
	while (res != str)
	{
		res--;
		if ((unsigned char)*res == (unsigned char)ch)
			return (res);
	}
	return (NULL);
}
