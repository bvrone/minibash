/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:54:02 by aglady            #+#    #+#             */
/*   Updated: 2021/04/06 16:54:05 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"

int	exec_command(t_cmds_pipeline *pipeline, int *tmp)
{
	int	res;

	if (((t_command *)pipeline->cmds->data)->red_fd[0] != -1)
		dup2(((t_command *)pipeline->cmds->data)->red_fd[0], 0);
	else
		dup2(tmp[0], 0);
	if (((t_command *)pipeline->cmds->data)->red_fd[1] != -1)
		dup2(((t_command *)pipeline->cmds->data)->red_fd[1], 1);
	else
		dup2(tmp[1], 1);
	res = execute_builtins(pipeline, pipeline->cmds);
	if (res == -1)
		execute_not_builtins(pipeline, pipeline->cmds);
	close(((t_command *)pipeline->cmds->data)->red_fd[0]);
	close(((t_command *)pipeline->cmds->data)->red_fd[1]);
	return (res);
}

int	ft_executor(t_cmds_pipeline *pipeline)
{
	int		tmp[2];
	int		res;

	tmp[0] = dup(0);
	tmp[1] = dup(1);
	if (!pipeline->cmds)
		return (0);
	if (!pipeline->cmds->next)
		res = exec_command(pipeline, tmp);
	else
		res = exec_pipeline(pipeline, tmp);
	dup2(tmp[0], 0);
	dup2(tmp[1], 1);
	close(tmp[0]);
	close(tmp[1]);
	return (res);
}
