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
		return ;
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
		ft_putendl_fd("minishell: cd: HOME not set", 2);
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

int	cd_dir(t_cmds_pipeline *pipeline, t_list *cmds)
{
	int			res;
	char		*tmp;

	errno = 0;
	tmp = get_pwd();
	res = chdir(((t_command *)(cmds->data))->argv[1]);
	if (res == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(((t_command *)(cmds->data))->argv[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	set_envp(pipeline->envp, "OLDPWD=", tmp);
	free(tmp);
	tmp = get_pwd();
	set_envp(pipeline->envp, "PWD=", tmp);
	if (!tmp)
		put_error("getcwd", strerror(errno));
	free(tmp);
	return (0);
}

int	ft_cd(t_cmds_pipeline *pipeline, t_list *cmds)
{
	if (((t_command *)(cmds->data))->argc == 1)
	{
		pipeline->last_ret_code = cd_home(pipeline);
		return (pipeline->last_ret_code);
	}
	pipeline->last_ret_code = cd_dir(pipeline, cmds);
	return (pipeline->last_ret_code);
}
