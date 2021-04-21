/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_matrix_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:55:10 by bvrone            #+#    #+#             */
/*   Updated: 2021/04/21 17:55:20 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t		set_values_in_lexemes(char **matrix, size_t i, size_t end,
								t_cmds_pipeline *pipeline)
{
	while (i < end)
	{
		if (matrix[i][0] == '\\')
			symbol_shielding(matrix, &i);
		else if (matrix[i][0] == '$')
		{
			if (!handle_dollar(matrix, &i, pipeline))
				return (0);//malloc error
		}
		else if (matrix[i][0] == '\'' || matrix[i][0] == '"')
		{
			if (!handle_quotes(matrix, &i, pipeline))
				return (0);//malloc error
		}
		i++;
	}
	return (1);
}

int		get_argc(char **matrix, size_t i, size_t cmd_end)
{
	int argc;

	argc = 0;
	while (i < cmd_end)
	{
		while (i < cmd_end && (matrix[i][0] == -1 || !matrix[i][0]))
			i++;
		if (i < cmd_end && matrix[i][0])
			argc++;
		while (i < cmd_end && matrix[i][0] != -1)
			i++;
	}
	return (argc);
}

char	*get_arg(char **matrix, size_t *cmd_i, size_t cmd_end)
{
	size_t	arg_len;
	size_t	i;
	size_t	arg_end;
	char	*arg;

	arg_len = 0;
	while (*cmd_i < cmd_end && (matrix[*cmd_i][0] == -1 || !matrix[*cmd_i][0]))
		*cmd_i += 1;
	arg_end = *cmd_i;
	while (arg_end < cmd_end && matrix[arg_end][0] != -1)
	{
		arg_len += ft_strlen(matrix[arg_end]);
		arg_end++;
	}
	arg = malloc(arg_len + 1);
	if (!arg)
		return (NULL);
	i = 0;
	while (*cmd_i < arg_end)
	{
		i += ft_strlcpy(arg + i, matrix[*cmd_i], arg_len + 1 - i);
		*cmd_i += 1;
	}
	return (arg);
}

char	**get_argv(char **matrix, size_t *cmd_i, size_t cmd_end, size_t argc)
{
	char	**argv;
	size_t	i;
	
	argv = malloc(argc * sizeof(char *) + 1);
	if (!argv)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		argv[i] = get_arg(matrix, cmd_i, cmd_end);
		if (!argv[i])
			return (clear_matrix(matrix, i));
		i++;
	}
	argv[i] = NULL;
	return (argv);
}