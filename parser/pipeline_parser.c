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

int	parse_cmd(char **matrix, size_t i, size_t cmd_end,
				t_cmds_pipeline *pipeline)
{
	while (i < cmd_end)
	{
		if (matrix[i][0] == '\\')
			symbol_shielding(matrix, &i);
		else if (matrix[i][0] == '$')
		{
			if (!handle_dollar(matrix, &i, pipeline))
				error_exit("malloc", "memory allocation fail", 2);
		}
		else if (matrix[i][0] == '\'' || matrix[i][0] == '"')
		{
			if (!handle_quotes(matrix, &i, pipeline))
				error_exit("malloc", "memory allocation fail", 2);
		}
		else if (matrix[i][0] == '<' || matrix[i][0] == '>')
			if (handle_redirect(matrix, &i, cmd_end, pipeline) == -1)
				return (-1);
		i++;
	}
	return (1);
}

void	set_cmd_to_pipeline(char **matrix,
							t_start_end *cmd_i,
							t_cmds_pipeline *pipeline,
							char *line)
{
	t_list		*new_lst;
	t_command	*new_cmd;
	int			argc;

	argc = get_argc(matrix, cmd_i->start, cmd_i->end, line);
	if (!argc)
		return ;
	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		error_exit("malloc", "memory allocation fail", 2);
	new_cmd->argc = argc;
	new_cmd->argv = get_argv(matrix, &cmd_i->start, cmd_i->end, argc);
	new_cmd->red_fd[0] = pipeline->tmp_fdin;
	new_cmd->red_fd[1] = pipeline->tmp_fdout;
	pipeline->tmp_fdin = -1;
	pipeline->tmp_fdout = -1;
	if (!new_cmd->argv)
		error_exit("malloc", "memory allocation fail", 2);
	new_lst = ft_lstnew(new_cmd);
	if (!new_lst)
		error_exit("malloc", "memory allocation fail", 2);
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

int	parse_pipeline(char **symbol_matrix,
					size_t *cur_i,
					t_cmds_pipeline *pipeline,
					char *line)
{
	size_t	cmd_end;

	while (symbol_matrix[*cur_i] && symbol_matrix[*cur_i][0] != ';')
	{
		if (symbol_matrix[*cur_i][0] == '|')
			*cur_i += 1;
		cmd_end = get_cmd_end(symbol_matrix, *cur_i);
		if (parse_cmd(symbol_matrix, *cur_i, cmd_end, pipeline) == -1)
			return (-1);
		set_cmd_to_pipeline(symbol_matrix, &(t_start_end){(*cur_i), cmd_end},
			pipeline, line);
		*cur_i = cmd_end;
	}
	if (symbol_matrix[*cur_i])
		*cur_i += 1;
	return (1);
}
