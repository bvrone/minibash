/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 19:32:56 by bvrone            #+#    #+#             */
/*   Updated: 2021/04/23 19:32:59 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_structures.h"

void	put_error(char *target, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}

void	error_exit(char *target, char *msg, int ret_code)
{
	put_error(target, msg);
	exit(ret_code);
}
