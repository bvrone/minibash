/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:33:02 by bvrone            #+#    #+#             */
/*   Updated: 2021/04/21 16:33:18 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_filename_syntax(char **matrix, size_t *i)
{
	*i += 1;
	skip_spaces(matrix, i);
	if (!matrix[*i])
		return (0);
	else if (matrix[*i][0] == '|' || matrix[*i][0] == ';')
		return (0);
	else if (matrix[*i][0] == '#' || matrix[*i][0] == '&')
		return (0);
	else if (matrix[*i][0] == '<' || matrix[*i][0] == '>')
		return (0);
	return (1);
}

int	check_redir_syntax(char **symbol_matrix, size_t *i)
{
	if (symbol_matrix[*i][0] == '<')
		return (check_filename_syntax(symbol_matrix, i));
	else if (symbol_matrix[*i][0] == '>')
	{
		if (symbol_matrix[*i + 1] && symbol_matrix[*i + 1][0] == '>')
			*i += 1;
		return (check_filename_syntax(symbol_matrix, i));
	}
	return (1);
}

int	check_shielding_syntax(char **matrix, size_t *i)
{
	*i += 1;
	if (!matrix[*i])
		return (0);
	return (1);
}

void	comment_start(char **symbol_matrix, size_t *i)
{
	if (*i == 0 || symbol_matrix[*i - 1][0] == -1)
	{
		while (symbol_matrix[*i])
		{
			symbol_matrix[*i][0] = -1;
			*i += 1;
		}
		*i -= 1;
	}
}
