/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_matrix_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:41:24 by bvrone            #+#    #+#             */
/*   Updated: 2021/04/21 16:41:38 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_key_from_m(char **matrix, size_t key_start, size_t key_len)
{
	char	*key;
	size_t	i;

	key = malloc(key_len + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (i < key_len)
	{
		key[i] = matrix[key_start + i][0];
		matrix[key_start + i][0] = 0;
		i++;
	}
	key[i] = 0;
	return (key);
}

size_t	env_value_to_m(char **matrix, size_t *dollar_i, t_env_var *env_var)
{
	char	*value;

	value = ft_strdup(env_var->value);
	if (!value)
		return (0);
	free(matrix[*dollar_i]);
	matrix[*dollar_i] = value;
	return (1);
}

void	*clear_matrix(char **matrix, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (NULL);
}

char	**split_line_to_matrix(char *line)
{
	char	**symbol_matrix;
	size_t	line_len;
	size_t	i;

	i = 0;
	line_len = ft_strlen(line);
	symbol_matrix = malloc(line_len * (sizeof(char *) + 1));
	if (!symbol_matrix)
		return (NULL);
	while (i < line_len)
	{
		symbol_matrix[i] = ft_substr(line, i, 1);
		if (!symbol_matrix[i])
			return (clear_matrix(symbol_matrix, i));
		i++;
	}
	symbol_matrix[i] = NULL;
	return (symbol_matrix);
}

int	split_to_lexemes(char **matrix, size_t *i)
{
	while (matrix[*i])
	{
		if (ft_strchr(SPACES, matrix[*i][0]))
			matrix[*i][0] = -1;
		else if (matrix[*i][0] == '\\')
		{
			if (!check_shielding_syntax(matrix, i))
				return (0);
		}
		else if (matrix[*i][0] == '#')
			comment_start(matrix, i);
		else if (matrix[*i][0] == '\'' || matrix[*i][0] == '"')
		{
			if (!skip_quotes(matrix, i))
				return (0);
		}
		else if (matrix[*i][0] == '<' || matrix[*i][0] == '>')
			if (!check_redir_syntax(matrix, i))
				return (0);
		*i += 1;
	}
	return (1);
}
