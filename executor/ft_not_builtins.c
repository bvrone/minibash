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

void	exec_with_path(t_list *cmds, char **envp)
{
	int	res;

	errno = 0;
	res = execve(((t_command *)(cmds->data))->argv[0],
			((t_command *)(cmds->data))->argv, envp);
	if (res == -1)
	{
		error_exit(((t_command *)(cmds->data))->argv[0],
			strerror(errno), 1);
	}
}

int	exec_full_path(t_list *cmds, char **envp, char *argv0, char *paths_i)
{
	char	*comm;
	int		res;

	res = -1;
	comm = ft_strjoin(paths_i, "/");
	if (!comm)
		error_exit("malloc", "Memory malloc failed", 2);
	((t_command *)(cmds->data))->argv[0] = ft_strjoin(comm,
			argv0);
	if (!((t_command *)(cmds->data))->argv[0])
		error_exit("malloc", "Memory malloc failed", 2);
	res = execve(((t_command *)(cmds->data))->argv[0],
			((t_command *)(cmds->data))->argv, envp);
	free(comm);
	free(((t_command *)(cmds->data))->argv[0]);
	return (res);
}

void	exec_not_path(t_cmds_pipeline *pipeline, t_list *cmds, char **envp)
{
	t_list	*path;
	char	**paths;
	int		i;
	int		res;
	char	*argv0;

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
		res = exec_full_path(cmds, envp, argv0, paths[i]);
		i++;
	}
	if (res == -1)
		error_exit(argv0, "command not found", 127);
}

void	sigterm_hand(int sig)
{
	(void)sig;
	error_exit("", "Terminated", 143);
}

void	exec_one_not_builtins(t_cmds_pipeline *pipeline, t_list *cmds)
{
	char	**envp;

	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	envp = list_to_envp(pipeline->envp);
	if (!envp)
		error_exit("malloc", "Memory malloc failed", 2);
	if (((t_command *)(cmds->data))->argv[0][0] == '.'
	|| ((t_command *)(cmds->data))->argv[0][0] == '/'
	|| ((t_command *)(cmds->data))->argv[0][0] == '~')
		exec_with_path(cmds, envp);
	else
		exec_not_path(pipeline, cmds, envp);
}

void	execute_not_builtins(t_cmds_pipeline *pipeline, t_list *cmds)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid < 0)
		error_exit("fork", "Can't create child process", 3);
	if (pid == 0)
		exec_one_not_builtins(pipeline, cmds);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			pipeline->last_ret_code = WEXITSTATUS(status);
		else
		{
			if (WTERMSIG(status) == SIGTERM)
			{
				ft_putendl_fd("Terminated", 2);
				pipeline->last_ret_code = 143;
			}
			else if (WTERMSIG(status) == SIGINT)
			{
				write(1, "\n", 2);
				pipeline->last_ret_code = 130;
			}
			else if (WTERMSIG(status) == SIGQUIT)
			{
				ft_putendl_fd("Quit: 3", 2);
				pipeline->last_ret_code = 131;
			}
		}
	}
}
