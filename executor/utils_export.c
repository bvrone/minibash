/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:33:18 by aglady            #+#    #+#             */
/*   Updated: 2021/04/30 21:33:25 by aglady           ###   ########.fr       */
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
