/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:31:57 by aglady            #+#    #+#             */
/*   Updated: 2021/04/06 17:31:59 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"

int	ft_env(t_cmds_pipeline *pipeline, t_list *cmds)
{
	t_list		*tmp;
	t_env_var	*cur;

	(void)cmds;
	tmp = pipeline->envp;
	while (tmp)
	{
		cur = (t_env_var *)(tmp->data);
		if (cur->value && cur->exp)
		{
			ft_putstr_fd(cur->key, 1);
			ft_putendl_fd(cur->value, 1);
		}
		tmp = tmp->next;
	}
	pipeline->last_ret_code = 0;
	return (0);
}
