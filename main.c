/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 01:25:08 by bvrone            #+#    #+#             */
/*   Updated: 2021/04/07 01:25:13 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_executor.h"
#include "termcup.h"

void	process_shline(char **symbol_matrix,
						t_cmds_pipeline *pipeline,
						char *line)
{
	size_t	pipeline_i;

	if (!split_to_lexemes(symbol_matrix) || !check_seprs_syntax(symbol_matrix))
		return ;
	pipeline_i = 0;
	while (symbol_matrix[pipeline_i])
	{
		if (parse_pipeline(symbol_matrix, &pipeline_i, pipeline, line) == -1)
			return (clear_pipeline(pipeline));
		ft_executor(pipeline);
		clear_pipeline(pipeline);
	}
}

void	init_vars(t_cmds_pipeline *pipeline, char *envp[])
{
	pipeline->cmds = NULL;
	pipeline->tmp_fdin = -1;
	pipeline->tmp_fdout = -1;
	pipeline->last_ret_code = 0;
	envp_to_list(pipeline, envp);
	if (!add_to_envp_if_not("OLDPWD", &pipeline->envp))
		exit(2);
	if (!inc_shlvl(pipeline))
		exit(2);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

void	main_loop(t_cmds_pipeline *pipeline)
{
	int				res;
	char			*line;
	char			**symbol_matrix;

	while (1)
	{
		ft_putstr_fd("minishell$ ", 2);
		res = termcup(&line);
		if (!res)
			exit(0);
		if (res < 0)
			exit(2);
		if (res == 2)
		{
			pipeline->last_ret_code = 1;
			continue ;
		}
		symbol_matrix = split_line_to_matrix(line);
		if (!symbol_matrix)
			exit(1);
		process_shline(symbol_matrix, pipeline, line);
		free(line);
		ft_split_clear(symbol_matrix);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_cmds_pipeline	pipeline;

	(void)argc;
	(void)argv;
	init_vars(&pipeline, envp);
	main_loop(&pipeline);
	return (0);
}
