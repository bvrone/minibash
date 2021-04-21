/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:20:11 by aglady            #+#    #+#             */
/*   Updated: 2020/11/03 15:16:15 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	size_t			len;
	unsigned int	i;

	res = NULL;
	if (s)
	{
		len = ft_strlen(s);
		res = (char *)malloc((len + 1) * sizeof(char));
		if (res)
		{
			i = 0;
			while (s[i])
			{
				res[i] = (*f)(i, s[i]);
				i++;
			}
			res[i] = '\0';
		}
	}
	return (res);
}
