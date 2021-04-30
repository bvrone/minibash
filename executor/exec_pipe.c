/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 20:49:39 by aglady            #+#    #+#             */
/*   Updated: 2021/04/30 20:49:44 by aglady           ###   ########.fr       */
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

void	close_pipe(t_cmds_pipeline *pipeline, int ***pipe_fd,
				size_t n, size_t i)
{
	if (i == 0)
		close(pipeline->fdin);
	else
		close((*pipe_fd)[i - 1][0]);
	if (i == n - 1)
		close(pipeline->fdout);
	else
		close((*pipe_fd)[i][1]);
}

int	get_in_out(t_cmds_pipeline *pipeline, int *tmp, int k)
{
	if (k == 0)
	{
		if (pipeline->fdin != -1)
			return (pipeline->fdin);
		return (tmp[0]);
	}
	if (pipeline->fdout != -1)
		return (pipeline->fdout);
	return (tmp[1]);
}

void	exec_pipe(t_cmds_pipeline *pipeline, int **pipe_fd, size_t n, int *tmp)
{
	size_t	i;
	int		res;

	i = 0;
	while (i < n)
	{
		if (i == 0)
			dup2(get_in_out(pipeline, tmp, 0), 0);
		else
			dup2(pipe_fd[i - 1][0], 0);
		if (i == n - 1)
			dup2(get_in_out(pipeline, tmp, 1), 1);
		else
			dup2(pipe_fd[i][1], 1);
		res = execute_builtins(pipeline, ft_lstind(pipeline->cmds, i));
		if (res == -1)
			execute_not_builtins(pipeline, ft_lstind(pipeline->cmds, i));
		close_pipe(pipeline, &pipe_fd, n, i);
		i++;
	}
}

int	exec_pipeline(t_cmds_pipeline *pipeline, int *tmp)
{
	size_t	n;
	size_t	i;
	int		**pipe_fd;

	if (init_pipe_fd(pipeline, &n, &pipe_fd))
		return (1);
	exec_pipe(pipeline, pipe_fd, n, tmp);
	i = 0;
	while (i < n - 1)
	{
		free(pipe_fd[i]);
		i++;
	}
	free(pipe_fd);
	return (pipeline->last_ret_code);
}
