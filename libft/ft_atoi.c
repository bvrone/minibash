/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 01:40:28 by aglady            #+#    #+#             */
/*   Updated: 2020/11/02 20:40:30 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long int	res;
	int			sign;
	char		*t;

	res = 0;
	t = (char *)str;
	sign = 1;
	while (*t == ' ' || *t == '\r' || *t == '\n'
		|| *t == '\t' || *t == '\v' || *t == '\f')
		t++;
	if (*t == '-' || *t == '+')
	{
		if (*t == '-')
			sign = -1;
		t++;
	}
	while (*t && *t >= '0' && *t <= '9')
	{
		res = res * 10 + (*t - '0');
		if (res * 10 < res)
			return ((-1 - sign) / 2);
		t++;
	}
	return (sign * (int)res);
}

int	ft_atoi_s(char **str)
{
	int		res;

	res = 0;
	while (**str == ' ')
		(*str)++;
	while (**str && **str >= '0' && **str <= '9')
	{
		res = res * 10 + (**str - '0');
		if (res * 10 < res)
			return (-1);
		(*str)++;
	}
	return (res);
}
