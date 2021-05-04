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

int	get_child_sig_retcode(int status)
{
	if (WTERMSIG(status) == SIGTERM)
	{
		ft_putstr_fd("Terminated: ", 2);
		ft_putnbr_fd(SIGTERM, 2);
		ft_putchar_fd('\n', 2);
		return (143);
	}
	else if (WTERMSIG(status) == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		return (130);
	}
	else if (WTERMSIG(status) == SIGQUIT)
	{
		ft_putendl_fd("Quit: 3", 2);
		return (131);
	}
	return (0);
}

int	get_child_retcode(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (get_child_sig_retcode(status));
}

void	exec_pipes(t_cmds_pipeline *pipeline, size_t i, int *pid)
{
	int	res;

	res = execute_builtins(pipeline, ft_lstind(pipeline->cmds, i));
	if (res == -1)
	{	
		pid[i] = fork();
		if (pid[i] < 0)
			error_exit("fork", "Can't create child process", 3);
		if (pid[i] == 0)
			exec_one_not_builtins(pipeline, ft_lstind(pipeline->cmds, i));
	}	
}

void	exec_pipe(t_cmds_pipeline *pipeline, int **pipe_fd,
			size_t n, int *in_out)
{
	size_t	i;
	int		status;
	int		*pid;

	pid = malloc(n * sizeof(int));
	if (!pid)
		error_exit("malloc", "Memory allocation failed", 2);
	i = 0;
	while (i < n)
	{
		set_in_out(pipeline, in_out, pipe_fd, i);
		exec_pipes(pipeline, i, pid);
		close_pipe_fd(pipeline, pipe_fd, n, i);
		i++;
	}
	i = 0;
	while (i < n)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	pipeline->last_ret_code = get_child_retcode(status);
	free(pid);
}

int	exec_pipeline(t_cmds_pipeline *pipeline, int *tmp)
{
	size_t	n;
	size_t	i;
	int		**pipe_fd;
	int		in_out[2];

	n = ft_lstsize(pipeline->cmds);
	if (init_pipe_fd(&pipe_fd, n - 1))
		return (1);
	init_in_out(pipeline, tmp, n, in_out);
	exec_pipe(pipeline, pipe_fd, n, in_out);
	i = 0;
	while (i < n - 1)
	{
		free(pipe_fd[i]);
		i++;
	}
	free(pipe_fd);
	return (pipeline->last_ret_code);
}
