/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:23:46 by aglady            #+#    #+#             */
/*   Updated: 2020/11/03 15:22:11 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;

	res = NULL;
	if (s)
	{
		res = (char *)malloc((len + 1) * sizeof(char));
		if (res)
		{
			i = 0;
			if (start < ft_strlen(s))
			{
				while (s[start + i] && i < len)
				{
					res[i] = s[start + i];
					i++;
				}
			}
			res[i] = '\0';
		}
	}
	return (res);
}
