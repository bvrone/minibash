/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:32:07 by aglady            #+#    #+#             */
/*   Updated: 2021/04/06 17:32:09 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"

int	str_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_cmds_pipeline *pipeline)
{
	write(1, "exit\n", 5);
	if (((t_command *)(pipeline->cmds->data))->argc == 1)
		exit(pipeline->last_ret_code);
	if (!str_digit(((t_command *)(pipeline->cmds->data))->argv[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, ((t_command *)(pipeline->cmds->data))->argv[1],
			ft_strlen(((t_command *)(pipeline->cmds->data))->argv[1]));
		write(2, ": numeric argument required\n", 28);
		pipeline->last_ret_code = 255;
		exit(255);
	}
	if (((t_command *)(pipeline->cmds->data))->argc > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		pipeline->last_ret_code = 1;
		return (1);
	}
	pipeline->last_ret_code = (unsigned char)
		ft_atoi(((t_command *)(pipeline->cmds->data))->argv[1]);
	return (pipeline->last_ret_code);
}
