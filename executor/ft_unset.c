/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:31:43 by aglady            #+#    #+#             */
/*   Updated: 2021/04/06 17:31:48 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"

t_list	*search_env(t_list *envp, const char *key)
{
	t_list	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (!keycmp(key, ((t_env_var *)(tmp->data))->key))
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	invalid_key(char *key)
{
	int	i;

	if (key[0] != '_' && !ft_isalpha(key[0]))
		return (1);
	i = 1;
	while (key[i] && key[i] != '=')
	{
		if (key[i] != '_' && !ft_isalnum(key[i]))
			return (1);
		i++;
	}
	return (0);
}

void	delete_item(t_list **envp, t_list *for_del)
{
	t_list	*prev;

	if (for_del)
	{
		if (for_del == *envp)
		{
			(*envp) = (*envp)->next;
		}
		else
		{
			prev = *envp;
			while (prev->next != for_del)
				prev = prev->next;
			prev->next = for_del->next;
		}
		free(((t_env_var *)(for_del->data))->key);
		free(((t_env_var *)(for_del->data))->value);
		free(for_del->data);
		free(for_del);
	}
}

int	delete_envp(t_list **envp, char *arg)
{
	t_list	*for_del;

	if (invalid_key(arg))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	for_del = search_env(*envp, arg);
	if ((!ft_strcmp(arg, "OLDPWD") || !ft_strcmp(arg, "PWD")) && for_del)
	{
		((t_env_var *)(for_del->data))->exp = 0;
		return (0);
	}
	delete_item(envp, for_del);
	return (0);
}

int	ft_unset(t_cmds_pipeline *pipeline, t_list *cmds)
{
	int	i;
	int	res;

	res = 0;
	if (((t_command *)(cmds->data))->argc > 1)
	{
		i = 0;
		while (++i < ((t_command *)(cmds->data))->argc)
		{
			if (!pipeline->envp)
				return (1);
			res = delete_envp(&pipeline->envp, ((t_command *)
						(cmds->data))->argv[i]);
			if (res)
				break ;
		}
	}
	pipeline->last_ret_code = res;
	return (res);
}
