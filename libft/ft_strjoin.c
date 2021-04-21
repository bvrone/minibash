/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:53:18 by aglady            #+#    #+#             */
/*   Updated: 2020/11/03 15:13:18 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;
	size_t	i;

	res = NULL;
	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		res = (char *)malloc((len1 + len2 + 1) * sizeof(char));
		if (res)
		{
			i = -1;
			while (++i < len1)
				res[i] = s1[i];
			while (i - len1 < len2)
			{
				res[i] = s2[i - len1];
				i++;
			}
			res[i] = '\0';
		}
	}
	return (res);
}
