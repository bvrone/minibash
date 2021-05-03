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

int	init_pipe_fd(t_cmds_pipeline *pipeline, size_t *n, int ***pipe_fd)
{
	size_t	i;

	*n = ft_lstsize(pipeline->cmds);
	*pipe_fd = malloc((*n - 1) * sizeof(int *));
	if (!*pipe_fd)
		error_exit("malloc", "Memory allocation failed", 2);
	i = 0;
	while (i < *n - 1)
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

void	init_in_out(t_cmds_pipeline *pipeline, int *tmp, int *in_out)
{
	if (pipeline->fdin != -1)
		in_out[0] = pipeline->fdin;
	else
		in_out[0] = tmp[0];
	if (pipeline->fdout != -1)
		in_out[1] = pipeline->fdout;
	else
		in_out[1] = tmp[1];
}

void	set_in_out(int *in_out, int **pipe_fd, size_t n, size_t i)
{
	if (i == 0)
		dup2(in_out[0], 0);
	else
		dup2(pipe_fd[i - 1][0], 0);
	if (i == n - 1)
		dup2(in_out[1], 1);
	else
		dup2(pipe_fd[i][1], 1);
}

void	close_pipe_fd(t_cmds_pipeline *pipeline, int **pipe_fd,
		size_t n, size_t i)
{
	if (i == 0)
		close(pipeline->fdin);
	else
		close(pipe_fd[i - 1][0]);
	if (i == n - 1)
		close(pipeline->fdout);
	else
		close(pipe_fd[i][1]);
}
