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

size_t		handle_dquotes(char **matrix, size_t *i,  t_cmds_pipeline *pipeline)
{
	size_t skipd_symb_cnt;
	size_t res;

	*i += 1;
	skipd_symb_cnt = 1;
	while (matrix[*i][0] != '"')
	{
		if (matrix[*i][0] == '\\')
			*i += 1;
		else if (matrix[*i][0] == '$')
		{
			res = handle_dollar(matrix, i, pipeline);
			if (!res)
				return(0);//malloc error
			skipd_symb_cnt += res;
		}
		*i += 1;
		skipd_symb_cnt++;
	}
	return (skipd_symb_cnt);
}

size_t		handle_quotes(char **matrix, size_t *i, t_cmds_pipeline *pipeline)
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