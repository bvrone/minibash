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

int	ft_exit(t_cmds_pipeline *pipeline, t_list *cmds)
{
	write(1, "exit\n", 5);
	if (((t_command *)(cmds->data))->argc == 1)
		exit(pipeline->last_ret_code);
	if (!str_digit(((t_command *)(cmds->data))->argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(((t_command *)(cmds->data))->argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		pipeline->last_ret_code = 255;
		exit(255);
	}
	if (((t_command *)(cmds->data))->argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		pipeline->last_ret_code = 1;
		return (1);
	}
	pipeline->last_ret_code = (unsigned char)
		ft_atoi(((t_command *)(cmds->data))->argv[1]);
	return (pipeline->last_ret_code);
}
