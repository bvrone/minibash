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

void	ft_create_fdout(t_cmds_pipeline *pipeline, t_list *comm,
						int fd[], int tmpout)
{
	int		fdpipe[2];

	if (!comm->next)
	{
		if (pipeline->outfile)
		{
			fd[1] = open(pipeline->outfile,
					O_CREAT | O_WRONLY | O_TRUNC, 0655);
			if (fd[1] == -1)
			{
				write(2, "Cannot open file.\n", 18);
				exit(1);
			}
		}
		else
			fd[1] = dup(tmpout);
	}
	else
	{
		pipe(fdpipe);
		fd[1] = fdpipe[1];
		fd[0] = fdpipe[0];
	}
}

int	ft_work_pipe(t_cmds_pipeline *pipeline, int fd[], int tmpout)
{
	t_list	*comm;
	int		res;

	comm = pipeline->cmds;
	while (comm)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		ft_create_fdout(pipeline, comm, fd, tmpout);
		dup2(fd[1], 1);
		close(fd[1]);
		res = execute_builtins(pipeline);
		if (res == -1)
			execute_not_builtins(pipeline);
		comm = comm->next;
	}
	return (res);
}

int	ft_executor(t_cmds_pipeline *pipeline)
{
	int		tmpin;
	int		tmpout;
	int		fd[2];
	int		res;

	tmpin = dup(0);
	tmpout = dup(1);
	if (pipeline->infile)
	{
		fd[0] = open(pipeline->infile, O_RDONLY);
		if (fd[0] == -1)
		{
			write(2, "Cannot open file.\n", 18);
			exit(1);
		}
	}
	else
		fd[0] = dup(tmpin);
	res = ft_work_pipe(pipeline, fd, tmpout);
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	return (res);
}
