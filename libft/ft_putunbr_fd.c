/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:35:32 by aglady            #+#    #+#             */
/*   Updated: 2020/11/27 17:18:48 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunbr_fd(unsigned int nb, int fd)
{
	unsigned int	n;
	unsigned int	temp;

	temp = nb;
	n = 1;
	while (temp >= 10)
	{
		temp /= 10;
		n *= 10;
	}
	temp = nb;
	while (n > 0)
	{
		ft_putchar_fd('0' + (temp / n), fd);
		temp %= n;
		n /= 10;
	}
}

void	ft_putnunbr_fd(unsigned int nbr, int n, int fd)
{
	unsigned int	digit;

	if (n == 1)
	{
		ft_putchar_fd(nbr + '0', fd);
		return ;
	}
	digit = nbr % 10;
	ft_putnunbr_fd(nbr / 10, n - 1, fd);
	ft_putchar_fd(digit + '0', fd);
}
