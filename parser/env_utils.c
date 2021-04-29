/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:56:43 by bvrone            #+#    #+#             */
/*   Updated: 2021/04/09 16:56:48 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	set_env_var(t_env_var *var, char *envp_line)
{
	size_t i;

	i = 0;
	while (envp_line[i] && envp_line[i] != '=')
		i++;
	if (!envp_line[i])
	{
		var->key = ft_substr(envp_line, 0, i);
		if (!var->key)
			return (0);
		var->value = NULL;
	}
	else
	{
		var->key = ft_substr(envp_line, 0, i + 1);
		if (!var->key)
			return (0);
		var->value = ft_strdup(&envp_line[i + 1]);
		if (!var->value)
		{
			free(var->key);
			return (0);
		}
	}
	return (1);
}

t_env_var	*new_env_var(char *envp_line)
{
	t_env_var	*var;

	var = malloc(sizeof(t_env_var));
	if (!var)
		return (NULL);
	if (!set_env_var(var, envp_line))
	{
		free(var);
		return (NULL);
	}
	var->exp = 1;
	return (var);
}

void	envp_to_list(t_cmds_pipeline *pipeline, char *envp[])
{
	size_t		i;
	t_env_var	*var;
	t_list		*new_lst;

	i = 0;
	pipeline->envp = NULL;
	while (envp[i])
	{
		var = new_env_var(envp[i]); 
		if (!var)
			exit(2);//print memory allocation error
		new_lst = ft_lstnew(var);
		if (!new_lst)
			exit(2);//print memory allocation error
		ft_lstadd_back(&pipeline->envp, new_lst);
		i++;
	}
}

t_env_var*	find_env_var(char *key, t_list *envp)
{
	while (envp)
	{
		if (!keycmp(key, ((t_env_var *)envp->data)->key))
			return (envp->data);
		envp = envp->next;
	}
	return (NULL);
}

char	**list_to_envp(t_list *list_envp)
{
	char	**envp;
	int		k;

	if (!list_envp)
		return (NULL);
	envp = (char **)malloc((ft_lstsize(list_envp) + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	k = 0;
	while (list_envp)
	{
		if (((t_env_var *)(list_envp->data))->value)
			envp[k] = ft_strjoin(((t_env_var *)(list_envp->data))->key,
					((t_env_var *)(list_envp->data))->value);
		else
			envp[k] = ft_strdup(((t_env_var *)(list_envp->data))->key);
		if (!envp[k])
			return (ft_split_clear(envp));
		k++;
		list_envp = list_envp->next;
	}
	envp[k] = 0;
	return (envp);
}