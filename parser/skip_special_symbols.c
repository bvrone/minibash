/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_symbols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:33:47 by bvrone            #+#    #+#             */
/*   Updated: 2021/04/21 17:34:00 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	skip_spaces(char **symbol_matrix, size_t *i)
{
	while (symbol_matrix[*i] && ft_strchr(SPACES, symbol_matrix[*i][0]))
	{
		symbol_matrix[*i][0] = -1;
		*i += 1;
	}
}

int		skip_double_quotes(char **symbol_matrix, size_t *i)
{
	*i += 1;
	if (!symbol_matrix[*i])
		return (0);
	while (symbol_matrix[*i][0] != '"')
	{
		*i += 1;
		if (symbol_matrix[*i][0] == '\\')
			*i += 1;
		if (!symbol_matrix[*i])
			return (0);
	}
	return (1);
}

size_t		skip_apostrophe(char **symbol_matrix, size_t *i)
{
	size_t skipd_symb_cnt;
	
	*i += 1;
	skipd_symb_cnt = 1;
	if (!symbol_matrix[*i])
		return (0);
	while (symbol_matrix[*i][0] != '\'')
	{
		*i += 1;
		if (!symbol_matrix[*i])
			return (0);
		skipd_symb_cnt++;
	}
	return (skipd_symb_cnt);
}

size_t		skip_quotes(char **symbol_matrix, size_t *i)
{
	if (symbol_matrix[*i][0] == '\'')
		return (skip_apostrophe(symbol_matrix, i));
	else if (symbol_matrix[*i][0] == '"')
		return (skip_double_quotes(symbol_matrix, i));
	return (1);
}

void	symbol_shielding(char **symbol_matrix, size_t *i)
{
	symbol_matrix[*i][0] = 0;
	*i += 1;
}