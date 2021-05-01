/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:26:37 by bvrone            #+#    #+#             */
/*   Updated: 2021/04/21 17:26:48 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	shielding_in_dquotesd(char **m, size_t *i)
{
	if (m[*i + 1][0] == '\\' || m[*i + 1][0] =='"' || m[*i + 1][0] =='$')
		symbol_shielding(m, i);
	else
		*i += 1;
}

size_t	handle_dquotes(char **matrix, size_t *i, t_cmds_pipeline *pipeline)
{
	size_t	skipd_symb_cnt;
	size_t	res;

	*i += 1;
	skipd_symb_cnt = 1;
	while (matrix[*i][0] != '"')
	{
		if (matrix[*i][0] == '\\')
			shielding_in_dquotesd(matrix, i);
		else if (matrix[*i][0] == '$')
		{
			res = handle_dollar(matrix, i, pipeline);
			if (!res)
				return (0);
			skipd_symb_cnt += res;
		}
		*i += 1;
		skipd_symb_cnt++;
	}
	return (skipd_symb_cnt);
}

size_t	handle_quotes(char **matrix, size_t *i, t_cmds_pipeline *pipeline)
{
	size_t	res;

	res = 1;
	if (matrix[*i][0] == '\'')
	{
		matrix[*i][0] = 0;
		res = skip_apostrophe(matrix, i);
		matrix[*i][0] = 0;
	}
	else if (matrix[*i][0] == '"')
	{
		matrix[*i][0] = 0;
		res = handle_dquotes(matrix, i, pipeline);
		matrix[*i][0] = 0;
	}
	return (res);
}
