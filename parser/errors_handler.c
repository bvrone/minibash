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

int	put_syntax_error_sep_token(char **matrix, size_t i)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (matrix[i + 1])
	{
		if (matrix[i][0] == matrix[i + 1][0])
			ft_putchar_fd(matrix[i + 1][0], 2);
	}
	ft_putchar_fd(matrix[i][0], 2);
	ft_putendl_fd("'", 2);
	return (0);
}

int	put_multiline_syntax_error(void)
{
	ft_putendl_fd("minishell: multi-line commands are not supported", 2);
	return (0);
}

int	put_syntax_error_redir(char **matrix, size_t i)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (matrix[i])
		ft_putchar_fd(matrix[i][0], 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putendl_fd("'", 2);
	return (0);
}

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
