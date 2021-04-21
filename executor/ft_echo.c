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

int	ft_echo(t_cmds_pipeline *pipeline)
{
	int	i;
	int	is_not_n;

	is_not_n = 1;
	if (((t_command *)(pipeline->cmds->data))->argc > 1)
	{
		is_not_n = ft_strcmp(((t_command *)(pipeline->cmds->data))->argv[1],
				"-n");
		i = 1;
		while (!ft_strcmp(((t_command *)(pipeline->cmds->data))->argv[i],
			"-n"))
			i++;
		while (i < ((t_command *)(pipeline->cmds->data))->argc)
		{
			write(1, ((t_command *)(pipeline->cmds->data))->argv[i],
				ft_strlen(((t_command *)(pipeline->cmds->data))->argv[i]));
			if (i < ((t_command *)(pipeline->cmds->data))->argc - 1)
				write(1, " ", 1);
			i++;
		}
	}
	if (is_not_n)
		write(1, "\n", 1);
	pipeline->last_ret_code = 0;
	return (0);
}
