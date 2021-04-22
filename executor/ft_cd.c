/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:31:13 by aglady            #+#    #+#             */
/*   Updated: 2021/04/06 17:31:15 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"

char	*get_pwd(void)
{
	char	*buf;
	size_t	size;

	size = 100;
	buf = NULL;
	buf = getcwd(buf, size);
	return (buf);
}

void	set_envp(t_list *envp, const char *key, char *value)
{
	char	*arg;

	arg = ft_strjoin(key, value);
	if (!arg)
		exit(2);
	insert_env(envp, arg);
	free(arg);
}

int	cd_home(t_cmds_pipeline *pipeline)
{
	t_list	*home;
	t_list	*pwd;

	home = search_env(pipeline->envp, "HOME=");
	if (!home || !(((t_env_var *)(home->data))->value))
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	pwd = search_env(pipeline->envp, "PWD=");
	if (!pwd || !(((t_env_var *)(pwd->data))->value))
		insert_env(pipeline->envp, "OLDPWD=");
	else
		set_envp(pipeline->envp, "OLDPWD=",
			(((t_env_var *)(pwd->data))->value));
	chdir((((t_env_var *)(home->data))->value));
	if (pwd)
		set_envp(pipeline->envp, "PWD=", get_pwd());
	return (0);
}

int	cd_dir(t_cmds_pipeline *pipeline)
{
	int		res;
	char	*tmp;

	errno = 0;
	tmp = get_pwd();
	res = chdir(((t_command *)(pipeline->cmds->data))->argv[1]);
	if (res == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, ((t_command *)(pipeline->cmds->data))->argv[1],
			ft_strlen(((t_command *)(pipeline->cmds->data))->argv[1]));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		return (1);
	}
	set_envp(pipeline->envp, "OLDPWD=", tmp);
	set_envp(pipeline->envp, "PWD=", get_pwd());
	free(tmp);
	return (0);
}

int	ft_cd(t_cmds_pipeline *pipeline)
{
	if (((t_command *)(pipeline->cmds->data))->argc == 1)
	{
		pipeline->last_ret_code = cd_home(pipeline);
		return (pipeline->last_ret_code);
	}
// 	if (!ft_strcmp(((t_command *)(pipeline->cmds->data))->argv[1], "-"))
// 		return (cd_minus(pipeline));
	pipeline->last_ret_code = cd_dir(pipeline);
	return (pipeline->last_ret_code);
}
