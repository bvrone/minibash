/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_not_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:42:12 by aglady            #+#    #+#             */
/*   Updated: 2021/04/21 13:42:14 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"

void	execute_not_builtins(t_cmds_pipeline *pipeline)
{
	int		pid;
	int		res;
	int		status;
	char	**envp;
	t_list	*path;
	char	**paths;
	int		i;
	char	*comm;

	pid = fork();
	if (pid < 0)
	{
		write(2, "minishell: Error fork\n", 22);
		exit(1);
	}
	if (pid == 0)
	{
		envp = list_to_envp(pipeline->envp);
		if (!envp)
		{
			write(2, "Error: list to envp\n", 20);
			exit(1);
		}
		if (((t_command *)(pipeline->cmds->data))->argv[0][0] == '.'
		|| ((t_command *)(pipeline->cmds->data))->argv[0][0] == '/'
		|| ((t_command *)(pipeline->cmds->data))->argv[0][0] == '~')
		{
			errno = 0;
			res = execve(((t_command *)(pipeline->cmds->data))->argv[0],
					((t_command *)(pipeline->cmds->data))->argv, envp);
			if (res == -1)
			{
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				exit(1);
			}
		}
		else
		{
			path = search_env(pipeline->envp, "PATH");
			if (!((t_env_var *)(path->data))->value)
				exit(1);
			paths = ft_split(((t_env_var *)(path->data))->value, ':');
			if (!paths)
				exit(1);
			i = 0;
			res = -1;
			while (paths[i])
			{
				comm = ft_strjoin(paths[i], "/");
				if (!comm)
					exit(1);
				comm = ft_strjoin(comm,
						((t_command *)(pipeline->cmds->data))->argv[0]);
				if (!comm)
					exit(1);
				errno = 0;
				res = execve(comm,
						((t_command *)(pipeline->cmds->data))->argv, envp);
				i++;
			}
			if (res == -1)
			{
				write(2, "minishell: ", 11);
				write(2, ((t_command *)(pipeline->cmds->data))->argv[0],
					ft_strlen(((t_command *)(pipeline->cmds->data))->argv[0]));
				write(2, ": command not found\n", 20);
				exit(1);
			}
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		pipeline->last_ret_code = WEXITSTATUS(status);
	}
}
