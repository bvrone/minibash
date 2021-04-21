/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 22:21:50 by aglady            #+#    #+#             */
/*   Updated: 2020/11/03 15:17:37 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_b;
	size_t	len_l;
	int		flag;

	len_b = ft_strlen(big);
	len_l = ft_strlen(little);
	if (len_l == 0)
		return ((char *)big);
	i = 0;
	while (i + len_l <= len_b && i + len_l <= len)
	{
		flag = 1;
		j = -1;
		while (++j < len_l && flag)
			if (big[i + j] != little[j])
				flag = 0;
		if (flag)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
