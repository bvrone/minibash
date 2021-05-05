/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:08:05 by aglady            #+#    #+#             */
/*   Updated: 2021/04/06 17:08:06 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"

int	is_key_n(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_cmds_pipeline *pipeline, t_list *cmds)
{
	int	i;
	int	is_not_n;

	is_not_n = 1;
	if (((t_command *)(cmds->data))->argc > 1)
	{
		i = 1;
		while (i < ((t_command *)(cmds->data))->argc &&
			is_key_n(((t_command *)(cmds->data))->argv[i]))
		{
			is_not_n = 0;	
			i++;
		}
		while (i < ((t_command *)(cmds->data))->argc)
		{
			ft_putstr_fd(((t_command *)(cmds->data))->argv[i], 1);
			if (i < ((t_command *)(cmds->data))->argc - 1)
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	if (is_not_n)
		write(1, "\n", 1);
	pipeline->last_ret_code = 0;
	return (0);
}
