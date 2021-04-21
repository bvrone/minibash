/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:22:07 by aglady            #+#    #+#             */
/*   Updated: 2020/11/03 15:03:17 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n, int *pow, int *sign)
{
	int		count;

	if (n < 0)
	{
		count = 2;
		*sign = -1;
	}
	else
	{
		count = 1;
		*sign = 1;
	}
	*pow = 1;
	while (n > 9 || n < -9)
	{
		n /= 10;
		*pow *= 10;
		count++;
	}
	return (count);
}

static char	*ft_zero(void)
{
	char	*res;

	res = (char *)malloc(2 * sizeof(char));
	if (res)
	{
		res[0] = '0';
		res[1] = '\0';
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		sign;
	int		pow;
	int		count;
	int		i;

	if (n == 0)
		return (ft_zero());
	count = ft_count_digits(n, &pow, &sign);
	res = (char *)malloc((count + 1) * sizeof(char));
	if (res)
	{
		i = 0;
		if (n < 0)
			res[i++] = '-';
		while (pow > 0)
		{
			res[i++] = '0' + sign * (n / pow);
			n %= pow;
			pow /= 10;
		}
		res[i] = '\0';
	}
	return (res);
}
