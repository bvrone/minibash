/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:31:23 by aglady            #+#    #+#             */
/*   Updated: 2021/04/06 17:31:25 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"

int	ft_pwd(t_cmds_pipeline *pipeline, t_list *cmds)
{
	t_env_var	*pwd;
	char		*buf;

	(void)cmds;
	pwd = find_env_var("PWD", pipeline->envp);
	buf = ft_strdup(pwd->value);
	if (!buf)
		error_exit("malloc", "memory allocation fail", 2);
	ft_putendl_fd(buf, 2);
	free(buf);
	pipeline->last_ret_code = 0;
	return (0);
}
