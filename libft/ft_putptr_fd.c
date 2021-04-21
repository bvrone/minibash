/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:18:03 by aglady            #+#    #+#             */
/*   Updated: 2020/11/27 18:52:59 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putxdigit(uintptr_t digit, int fd)
{
	if (digit >= 0 && digit <= 9)
		ft_putchar_fd('0' + digit, fd);
	else
		ft_putchar_fd('a' + (digit - 10), fd);
}

void	ft_putptr_fd(uintptr_t nb, int fd)
{
	uintptr_t	n;
	uintptr_t	temp;

	temp = nb;
	n = 1;
	while (temp >= 16)
	{
		temp /= 16;
		n *= 16;
	}
	temp = nb;
	while (n > 0)
	{
		ft_putxdigit(temp / n, fd);
		temp %= n;
		n /= 16;
	}
}

void	ft_putnptr_fd(uintptr_t nb, int n, int fd)
{
	uintptr_t	digit;

	if (n == 1)
	{
		ft_putxdigit(nb, fd);
		return ;
	}
	digit = nb % 16;
	ft_putnptr_fd(nb / 16, n - 1, fd);
	ft_putxdigit(digit, fd);
}
