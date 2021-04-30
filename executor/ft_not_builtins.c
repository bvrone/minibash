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

void	execute_not_builtins(t_cmds_pipeline *pipeline, t_list *cmds)
{
	int		pid;
	int		res;
	int		status;
	char	**envp;
	t_list	*path;
	char	**paths;
	int		i;
	char	*argv0;
	char	*comm;

	pid = fork();
	if (pid < 0)
		error_exit("exec", "Error fork", 1);
	if (pid == 0)
	{
		envp = list_to_envp(pipeline->envp);
		if (!envp)
			error_exit("malloc", "Memory malloc failed", 2);
		if (((t_command *)(cmds->data))->argv[0][0] == '.'
		|| ((t_command *)(cmds->data))->argv[0][0] == '/'
		|| ((t_command *)(cmds->data))->argv[0][0] == '~')
		{
			errno = 0;
			res = execve(((t_command *)(cmds->data))->argv[0],
					((t_command *)(cmds->data))->argv, envp);
			if (res == -1)
			{
				error_exit(((t_command *)(cmds->data))->argv[0],
					strerror(errno), 1);
			}
		}
		else
		{
			path = search_env(pipeline->envp, "PATH");
			if (!path || !((t_env_var *)(path->data))->value)
				return ;
			paths = ft_split(((t_env_var *)(path->data))->value, ':');
			if (!paths)
				error_exit("malloc", "Memory malloc failed", 2);
			i = 0;
			res = -1;
			argv0 = ft_strdup(((t_command *)(cmds->data))->argv[0]);
			while (paths[i])
			{
				comm = ft_strjoin(paths[i], "/");
				if (!comm)
					error_exit("malloc", "Memory malloc failed", 2);
				((t_command *)(cmds->data))->argv[0] = ft_strjoin(comm,
						argv0);
				if (!((t_command *)(cmds->data))->argv[0])
					error_exit("malloc", "Memory malloc failed", 2);
				errno = 0;
				res = execve(((t_command *)(cmds->data))->argv[0],
						((t_command *)(cmds->data))->argv, envp);
				i++;
				free(comm);
				free(((t_command *)(cmds->data))->argv[0]);
			}
			if (res == -1)
				error_exit(argv0, "command not found", 2);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		pipeline->last_ret_code = WEXITSTATUS(status);
	}
}
