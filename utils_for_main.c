/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 23:08:20 by aglady            #+#    #+#             */
/*   Updated: 2021/04/30 23:08:22 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_executor.h"
#include "termcup.h"

void	free_cmd(void *cmd)
{
	ft_split_clear(((t_command *)cmd)->argv);
	close(((t_command *)cmd)->red_fd[0]);
	close(((t_command *)cmd)->red_fd[1]);
	free(cmd);
	cmd = NULL;
}

void	clear_pipeline(t_cmds_pipeline *pipeline)
{
	ft_lstclear(&pipeline->cmds, &free_cmd);
	pipeline->tmp_fdin = -1;
	pipeline->tmp_fdout = -1;
}

int	add_to_envp_if_not(char *key, t_list **envp)
{
	t_env_var	*env_var;
	t_list		*new_lst;

	if (!find_env_var(key, *envp))
	{
		env_var = new_env_var(key);
		if (!env_var)
			error_exit("malloc", "Memory malloc failed", 2);
		new_lst = ft_lstnew(env_var);
		if (!new_lst)
			error_exit("malloc", "Memory malloc failed", 2);
		ft_lstadd_front(envp, new_lst);
	}
	return (1);
}

int	inc_shlvl(t_cmds_pipeline *pipeline)
{
	t_env_var	*shlvl_var;
	int			lvl;

	if (!add_to_envp_if_not("SHLVL=", &pipeline->envp))
		return (0);
	shlvl_var = find_env_var("SHLVL", pipeline->envp);
	if (shlvl_var->value)
	{
		lvl = ft_atoi(shlvl_var->value);
		lvl++;
		free(shlvl_var->value);
		shlvl_var->value = ft_itoa(lvl);
	}
	else
		shlvl_var->value = ft_strdup("1");
	if (!shlvl_var->value)
		return (0);
	return (1);
}
