/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:39:43 by aglady            #+#    #+#             */
/*   Updated: 2021/04/21 13:39:45 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"

int	ft_is_builtins(char *command)
{
	if (!ft_strcmp(command, "echo"))
		return (0);
	if (!ft_strcmp(command, "cd"))
		return (1);
	if (!ft_strcmp(command, "pwd"))
		return (2);
	if (!ft_strcmp(command, "export"))
		return (3);
	if (!ft_strcmp(command, "unset"))
		return (4);
	if (!ft_strcmp(command, "env"))
		return (5);
	if (!ft_strcmp(command, "exit"))
		return (6);
	return (-1);
}

void	init_builtins(int (*builtins[7])())
{
	builtins[0] = ft_echo;
	builtins[1] = ft_cd;
	builtins[2] = ft_pwd;
	builtins[3] = ft_export;
	builtins[4] = ft_unset;
	builtins[5] = ft_env;
	builtins[6] = ft_exit;
}

int	execute_builtins(t_cmds_pipeline *pipeline, t_list *cmds)
{
	int	num_command;
	int	res;
	int	(*builtins[7])();
	
	init_builtins(builtins);
	num_command = ft_is_builtins(
			((t_command *)(cmds->data))->argv[0]);
	if (num_command == -1)
		return (-1);
	res = builtins[num_command](pipeline, cmds);
	return (res);
}
