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
		error_exit("exec", "Error fork", 1);
	if (pid == 0)
	{
		envp = list_to_envp(pipeline->envp);
		if (!envp)
			error_exit("exec", "Error list to envp", 2);
		if (((t_command *)(pipeline->cmds->data))->argv[0][0] == '.'
		|| ((t_command *)(pipeline->cmds->data))->argv[0][0] == '/'
		|| ((t_command *)(pipeline->cmds->data))->argv[0][0] == '~')
		{
			errno = 0;
			res = execve(((t_command *)(pipeline->cmds->data))->argv[0],
					((t_command *)(pipeline->cmds->data))->argv, envp);
			if (res == -1)
				error_exit("exec", strerror(errno), 1);
		}
		else
		{
			path = search_env(pipeline->envp, "PATH");
			if (!((t_env_var *)(path->data))->value)
				return ;
			paths = ft_split(((t_env_var *)(path->data))->value, ':');
			if (!paths)
				error_exit("exec", "malloc error", 2);
			i = 0;
			res = -1;
			while (paths[i])
			{
				comm = ft_strjoin(paths[i], "/");
				if (!comm)
					error_exit("exec", "malloc error", 2);
				comm = ft_strjoin(comm,
						((t_command *)(pipeline->cmds->data))->argv[0]);
				if (!comm)
					error_exit("exec", "malloc error", 2);
				errno = 0;
				res = execve(comm,
						((t_command *)(pipeline->cmds->data))->argv, envp);
				i++;
			}
			if (res == -1)
				error_exit(((t_command *)(pipeline->cmds->data))->argv[0],
					"command not found", 1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		pipeline->last_ret_code = WEXITSTATUS(status);
	}
}
