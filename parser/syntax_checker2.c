/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:21:59 by bvrone            #+#    #+#             */
/*   Updated: 2021/04/22 21:22:01 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static	int	check_pipe_syntax(char **matrix, size_t pipe_i)
{
	size_t	i;

	if (!pipe_i)
		return (0);
	i = pipe_i - 1;
	while (i > 0 && matrix[i][0] == -1)
		i--;
	if (matrix[i][0] == -1 || matrix[i][0] == '|' || matrix[i][0] == ';')
		return (0);
	pipe_i++;
	while (matrix[pipe_i] && matrix[pipe_i][0] == -1)
		pipe_i++;
	if (!matrix[pipe_i])
		return (0);
	return (1);
}

static	int	check_cmdsep_syntax(char **matrix, size_t i)
{
	if (!i)
		return (0);
	i--;
	while (i > 0 && matrix[i][0] == -1)
		i--;
	if (matrix[i][0] == -1 || matrix[i][0] == '|' || matrix[i][0] == ';')
		return (0);
	return (1);
}

int	check_seprs_syntax(char **matrix)
{
	size_t	i;

	i = 0;
	while (matrix[i])
	{
		if (matrix[i][0] == '|')
		{
			if (!check_pipe_syntax(matrix, i))
				return (0);
		}
		else if (matrix[i][0] == ';')
		{
			if (!check_cmdsep_syntax(matrix, i))
				return (0);
		}
		else if (matrix[i][0] == '\'' || matrix[i][0] == '"')
		{
			if (!skip_quotes(matrix, &i))
				return (0);
		}
		i++;
	}
	return (1);
}
