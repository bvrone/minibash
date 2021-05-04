/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 22:29:08 by aglady            #+#    #+#             */
/*   Updated: 2021/05/02 22:29:10 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"

int	init_pipe_fd(int ***pipe_fd, size_t n)
{
	size_t	i;

	*pipe_fd = malloc(n * sizeof(int *));
	if (!*pipe_fd)
		error_exit("malloc", "Memory allocation failed", 2);
	i = 0;
	while (i < n)
	{
		(*pipe_fd)[i] = malloc(2 * sizeof(int));
		if (!(*pipe_fd)[i])
			error_exit("malloc", "Memory allocation failed", 2);
		if (pipe((*pipe_fd)[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

void	init_in_out(t_cmds_pipeline *pipeline, int *tmp, size_t n, int *in_out)
{
	if (((t_command *)ft_lstind(pipeline->cmds, 0)->data)->red_fd[0] != -1)
		in_out[0] = ((t_command *)ft_lstind(pipeline->cmds,
					0)->data)->red_fd[0];
	else
		in_out[0] = tmp[0];
	if (((t_command *)ft_lstind(pipeline->cmds, n - 1)->data)->red_fd[1] != -1)
		in_out[1] = ((t_command *)ft_lstind(pipeline->cmds,
					n - 1)->data)->red_fd[1];
	else
		in_out[1] = tmp[1];
}

void	set_in_out(t_cmds_pipeline *pipeline, int *in_out,
		int **pipe_fd, size_t i)
{
	size_t	n;

	n = ft_lstsize(pipeline->cmds);
	if (i == 0)
		dup2(in_out[0], 0);
	else
	{
		dup2(pipe_fd[i - 1][0], 0);
		if (((t_command *)ft_lstind(pipeline->cmds, i)->data)->red_fd[0] != -1)
			dup2(((t_command *)(ft_lstind(pipeline->cmds, i)->data))->red_fd[0],
				0);
	}
	if (i == n - 1)
		dup2(in_out[1], 1);
	else
	{
		dup2(pipe_fd[i][1], 1);
		if (((t_command *)ft_lstind(pipeline->cmds, i)->data)->red_fd[1] != -1)
			dup2(((t_command *)(ft_lstind(pipeline->cmds, i)->data))->red_fd[1],
				1);
	}
}

void	close_pipe_fd(t_cmds_pipeline *pipeline, int **pipe_fd,
				size_t n, size_t i)
{
	close(((t_command *)ft_lstind(pipeline->cmds, i)->data)->red_fd[0]);
	((t_command *)ft_lstind(pipeline->cmds, i)->data)->red_fd[0] = -1;
	close(((t_command *)ft_lstind(pipeline->cmds, i)->data)->red_fd[1]);
	((t_command *)ft_lstind(pipeline->cmds, i)->data)->red_fd[1] = -1;
	if (i > 0)
		close(pipe_fd[i - 1][0]);
	if (i < n - 1)
		close(pipe_fd[i][1]);
}
