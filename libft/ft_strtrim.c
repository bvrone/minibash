/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:33:23 by aglady            #+#    #+#             */
/*   Updated: 2020/11/04 16:42:51 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_find_beg(char const *s1, char const *set)
{
	char	*res;

	res = (char *)s1;
	while (*res && ft_strchr(set, *res))
		res++;
	return (res);
}

static char	*ft_find_end(char const *s1, char const *set)
{
	char	*res;

	if (!(*s1))
		return ((char *)s1);
	res = (char *)s1;
	while (*res)
		res++;
	res--;
	while (res != (char *)s1 && ft_strchr(set, *res))
		res--;
	if (res != (char *)s1)
		res++;
	return (res);
}

static char	*ft_create_result(char const *beg, char const *end)
{
	char	*res;
	size_t	i;

	res = (char *)malloc(end - beg + 1);
	if (res)
	{
		i = 0;
		while (beg + i < end)
		{
			res[i] = *(beg + i);
			i++;
		}
		res[i] = '\0';
	}
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	char	*beg;
	char	*end;

	res = NULL;
	if (s1 && set)
	{
		beg = ft_find_beg(s1, set);
		end = ft_find_end(s1, set);
		if (beg < end)
			res = ft_create_result(beg, end);
		else
		{
			if (beg)
				res = ft_create_result(beg, beg + 1);
			else
				res = ft_create_result(beg, beg);
		}
	}
	return (res);
}
