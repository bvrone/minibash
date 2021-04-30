/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:31:33 by aglady            #+#    #+#             */
/*   Updated: 2021/04/06 17:31:34 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"

int	check_var(t_env_var *var)
{
	if (!var)
		return (0);
	if (invalid_key(var->key))
	{
		write(2, "minishell: export: `", 20);
		write(2, var->key, ft_strlen(var->key));
		write(2, "': not a valid identifier\n", 26);
		return (0);
	}
	return (1);
}

int	replace_env(t_env_var *var, t_list *new_lst)
{
	free(((t_env_var *)(new_lst->data))->key);
	((t_env_var *)(new_lst->data))->key = ft_strdup(var->key);
	if (!((t_env_var *)(new_lst->data))->key)
		return (1);
	free(((t_env_var *)(new_lst->data))->value);
	((t_env_var *)(new_lst->data))->value = ft_strdup(var->value);
	if (!((t_env_var *)(new_lst->data))->value)
		return (1);
	return (0);
}

int	insert_env(t_list *envp, char *arg)
{
	t_env_var	*var;
	t_list		*new_lst;

	if (!ft_strcmp(arg, "PWD") && !search_env(envp, "PWD"))
	{
		free(arg);
		arg = ft_strjoin("PWD=", get_pwd());
		if (!arg)
			return (1);
	}
	var = new_env_var(arg);
	if (!check_var(var))
		return (1);
	new_lst = search_env(envp, var->key);
	if (!ft_strcmp(arg, "OLDPWD") && new_lst)
	{
		((t_env_var *)(new_lst->data))->exp = 1;
		return (0);
	}
	if (!new_lst)
	{
		new_lst = ft_lstnew(var);
		if (!new_lst)
			return (1);
		ft_lstadd_back(&envp, new_lst);
	}
	else
		return (replace_env(var, new_lst));
	return (0);
}

int	ft_export(t_cmds_pipeline *pipeline, t_list *cmds)
{
	int	i;
	int	res;

	res = 0;
	if (((t_command *)(cmds->data))->argc == 1)
	{
		show_export(pipeline->envp);
	}
	else
	{
		i = 0;
		while (++i < ((t_command *)(cmds->data))->argc)
		{
			res = insert_env(pipeline->envp, ((t_command *)
						(cmds->data))->argv[i]);
			if (res)
				break ;
		}
	}
	pipeline->last_ret_code = res;
	return (res);
}
