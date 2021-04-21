/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:57:17 by aglady            #+#    #+#             */
/*   Updated: 2020/11/27 17:18:18 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	int		n;
	int		temp;
	int		sign;

	sign = 1;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		sign = -1;
	}
	n = 1;
	temp = nb;
	while (temp >= 10 || temp <= -10)
	{
		temp /= 10;
		n *= 10;
	}
	temp = nb;
	while (n > 0)
	{
		ft_putchar_fd('0' + sign * (temp / n), fd);
		temp %= n;
		n /= 10;
	}
}

void	ft_putnnbr_fd(int nbr, int sign, int n, int fd)
{
	int			digit;

	if (n == 1)
	{
		if (sign == -1)
			ft_putchar_fd('-', fd);
		ft_putchar_fd(nbr * sign + '0', fd);
		return ;
	}
	digit = nbr % 10;
	ft_putnnbr_fd(nbr / 10, sign, n - 1, fd);
	ft_putchar_fd(digit * sign + '0', fd);
}
