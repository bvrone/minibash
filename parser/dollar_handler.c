/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:02:06 by bvrone            #+#    #+#             */
/*   Updated: 2021/04/21 17:02:19 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	set_ret_code(char **matrix, size_t *dollar_i, int last_ret_code)
{
	char	*var;

	var = ft_itoa(last_ret_code);
	if (!var)
		return (0);
	free(matrix[*dollar_i]);
	matrix[*dollar_i] = var;
	*dollar_i += 1;
	matrix[*dollar_i][0] = 0;
	return (1);
}

static size_t	replace_to_env(char **matrix, size_t *dollar_i, t_list *envp)
{
	size_t		i;
	size_t		res;
	t_env_var	*env_var;
	char		*key;

	i = *dollar_i + 2;
	res = 1;
	while (matrix[i] && (ft_isalnum(matrix[i][0]) || matrix[i][0] == '_'))
		i++;
	key = get_key_from_m(matrix, *dollar_i + 1, i - *dollar_i - 1);
	if (!key)
		return (0);
	env_var = find_env_var(key, envp);
	free(key);
	if (env_var)
		res = env_value_to_m(matrix, dollar_i, env_var);
	else
		matrix[*dollar_i][0] = 0;
	*dollar_i = i - 1;
	return (res);
}

size_t		handle_dollar(char **matrix, size_t *i, t_cmds_pipeline *pipeline)
{
	char	*var;
	
	if (matrix[*i + 1])
	{
		if (matrix[*i + 1][0] == '?')
			return (set_ret_code(matrix, i, pipeline->last_ret_code));
		else if (ft_isalpha(matrix[*i + 1][0]) || matrix[*i + 1][0] == '_')
			return (replace_to_env(matrix, i, pipeline->envp));
		else if (ft_isdigit(matrix[*i + 1][0]))
		{
			matrix[*i][0] = 0;
			matrix[*i + 1][0] = 0;
			*i += 1;
		}
	}
	return (1);
}