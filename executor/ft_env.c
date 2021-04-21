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

int	ft_env(t_cmds_pipeline *pipeline)
{
	t_list		*tmp;
	t_env_var	*cur;

	tmp = pipeline->envp;
	while (tmp)
	{
		cur = (t_env_var *)(tmp->data);
		if (cur->value)
		{
			write(1, cur->key, ft_strlen(cur->key));
			write(1, cur->value, ft_strlen(cur->value));
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	pipeline->last_ret_code = 0;
	return (0);
}
