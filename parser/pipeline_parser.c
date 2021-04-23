/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:45:31 by bvrone            #+#    #+#             */
/*   Updated: 2021/04/21 16:45:41 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		parse_cmd(char **matrix, size_t i, size_t cmd_end,
					t_cmds_pipeline *pipeline)
{
	while (i < cmd_end)
	{
		if (matrix[i][0] == '\\')
			symbol_shielding(matrix, &i);
		else if (matrix[i][0] == '$')
		{
			if (!handle_dollar(matrix, &i, pipeline))
				exit(2);//malloc error
		}
		else if (matrix[i][0] == '\'' || matrix[i][0] == '"')
		{
			if (!handle_quotes(matrix, &i, pipeline))
				exit(2);//malloc error
		}
		else if (matrix[i][0] == '<' || matrix[i][0] == '>')
			if (handle_redirect(matrix, &i, cmd_end, pipeline) == -1)
				return (-1);
		i++;
	}
	return (1);
}

void	set_cmd_to_pipeline(char **matrix, size_t *i, size_t cmd_end,
					t_cmds_pipeline *pipeline)
{
	t_list		*new_lst;
	t_command	*new_cmd;
	int			argc;
	
	argc = get_argc(matrix, *i, cmd_end);
	if (!argc)
		return;
	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		exit(2);//malloc error
	new_cmd->argc = argc;
	new_cmd->argv = get_argv(matrix, i, cmd_end, argc);
	if (!new_cmd->argv)
		exit(2);//malloc error
	new_lst = ft_lstnew(new_cmd);
	if (!new_lst)
		exit(2);//mallor error
	ft_lstadd_back(&pipeline->cmds, new_lst);
}

size_t	get_cmd_end(char **matrix, size_t i)
{
	while (matrix[i] && matrix[i][0] != ';' && matrix[i][0] != '|')
	{
		if (matrix[i][0] == '\\')
			i++;
		else if (matrix[i][0] == '\'' || matrix[i][0] == '"')
			skip_quotes(matrix, &i);
		i++;
	}
	return (i);
}

int		parse_pipeline(char **symbol_matrix, size_t *cur_i,
			t_cmds_pipeline *pipeline)
{
	size_t cmd_end;

	while (symbol_matrix[*cur_i] && symbol_matrix[*cur_i][0] != ';')
	{
		if (symbol_matrix[*cur_i][0] == '|')
			*cur_i += 1;
		cmd_end = get_cmd_end(symbol_matrix, *cur_i);
		if (parse_cmd(symbol_matrix, *cur_i, cmd_end, pipeline) == -1)
			return (-1);
		set_cmd_to_pipeline(symbol_matrix, cur_i, cmd_end, pipeline);
		*cur_i = cmd_end;
	}
	if (symbol_matrix[*cur_i])
		*cur_i += 1;
	return (1);
}