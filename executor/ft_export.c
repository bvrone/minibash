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

int	keycmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=' && s1[i] == s2[i])
		i++;
	if (s1[i] == '=' && s2[i] == '=')
		return (0);
	if (s1[i] == '=')
		return (- (unsigned char)s2[i]);
	if (s2[i] == '=')
		return ((unsigned char)s1[i]);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	sort_env(t_list *list_envp, t_list **sort_list)
{
	t_list		*tmp;
	t_list		*new_item;
	t_env_var	*var;

	if (!list_envp)
		*sort_list = NULL;
	*sort_list = ft_lstnew((t_env_var *)(list_envp->data));
	if (!(*sort_list))
	{
		write(1, "minishell: Memory allocation error\n", 35);
		exit(1);
	}
	list_envp = list_envp->next;
	while (list_envp)
	{
		var = (t_env_var *)(list_envp->data);
		if (keycmp(var->key, ((t_env_var *)((*sort_list)->data))->key) < 0)
		{
			new_item = ft_lstnew(var);
			if (!new_item)
			{
				write(1, "minishell: Memory allocation error\n", 35);
				exit(1);
			}
			ft_lstadd_front(sort_list, new_item);
		}
		else
		{
			tmp = *sort_list;
			while (tmp->next && (keycmp(var->key,
						((t_env_var *)(tmp->next->data))->key) > 0))
				tmp = tmp->next;
			new_item = ft_lstnew(var);
			if (!new_item)
			{
				write(1, "minishell: Memory allocation error\n", 35);
				exit(1);
			}
			new_item->next = tmp->next;
			tmp->next = new_item;
		}
		list_envp = list_envp->next;
	}
}

void	show_export(t_list *envp)
{
	t_list		*tmp;
	t_env_var	*cur;

	sort_env(envp, &tmp);
	while (tmp)
	{
		cur = (t_env_var *)(tmp->data);
		if (cur->exp)
		{
			write(1, "declare -x ", 11);
			write(1, cur->key, ft_strlen(cur->key));
			if (cur->value)
			{
				write(1, "\"", 1);
				write(1, cur->value, ft_strlen(cur->value));
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	ft_lstclear(&tmp, &free);
}

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

int	ft_export(t_cmds_pipeline *pipeline)
{
	int	i;
	int	res;

	res = 0;
	if (((t_command *)(pipeline->cmds->data))->argc == 1)
	{
		show_export(pipeline->envp);
	}
	else
	{
		i = 0;
		while (++i < ((t_command *)(pipeline->cmds->data))->argc)
		{
			res = insert_env(pipeline->envp, ((t_command *)
						(pipeline->cmds->data))->argv[i]);
			if (res)
				break ;
		}
	}
	pipeline->last_ret_code = res;
	return (res);
}
