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

int	ft_pwd(t_cmds_pipeline *pipeline)
{
	char	*buf;
	size_t	size;

	size = 100;
	buf = NULL;
	errno = 0;
	buf = getcwd(buf, size);
	if (!buf)
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		pipeline->last_ret_code = 1;
		return (1);
	}
	ft_putendl_fd(buf, 1);
	free(buf);
	pipeline->last_ret_code = 0;
	return (0);
}
