/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putxnbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 11:58:26 by aglady            #+#    #+#             */
/*   Updated: 2020/11/27 17:31:53 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putxdigit(unsigned int digit, int fd, char xx)
{
	if (digit >= 0 && digit <= 9)
		ft_putchar_fd('0' + digit, fd);
	else
	{
		if (xx == 'x')
			ft_putchar_fd('a' + (digit - 10), fd);
		else
			ft_putchar_fd('A' + (digit - 10), fd);
	}
}

void	ft_putxnbr_fd(unsigned int nb, int fd, char xx)
{
	unsigned int	n;
	unsigned int	temp;

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
		ft_putxdigit(temp / n, fd, xx);
		temp %= n;
		n /= 16;
	}
}

void	ft_putnxnbr_fd(unsigned int nbr, int n, int fd, char xx)
{
	unsigned int	digit;

	if (n == 1)
	{
		ft_putxdigit(nbr, fd, xx);
		return ;
	}
	digit = nbr % 16;
	ft_putnxnbr_fd(nbr / 16, n - 1, fd, xx);
	ft_putxdigit(digit, fd, xx);
}
