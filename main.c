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

void	put_error_syntax(char **matrix, size_t i)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putchar_fd(matrix[i - 1][0], 2);
	ft_putendl_fd("'", 2);
}

void	process_shline(char **symbol_matrix, t_cmds_pipeline *pipeline)
{
	size_t	pipeline_i;

	pipeline_i = 0;
	if (!split_to_lexemes(symbol_matrix, &pipeline_i) || 
		!check_seprs_syntax(symbol_matrix))
	{
		put_error_syntax(symbol_matrix, pipeline_i);
		clear_pipeline(pipeline);//вроде не надо вызывать
		return ;
	}
	pipeline_i = 0;
	while (symbol_matrix[pipeline_i])
	{
		if (parse_pipeline(symbol_matrix, &pipeline_i, pipeline) == -1)
			return (clear_pipeline(pipeline));
		ft_executor(pipeline);
		clear_pipeline(pipeline);
	}
}

void	handler(int sig)
{
	int	status;

	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (sig == SIGINT)
			write(1, "\n", 1);
		if (sig == SIGQUIT)
			ft_putendl_fd("Quit: 3", 1);
	}
}

void	init_vars(t_cmds_pipeline *pipeline, char *envp[])
{
	pipeline->cmds = NULL;
	pipeline->fdin = -1;
	pipeline->fdout = -1;
	pipeline->last_ret_code = 0;
	envp_to_list(pipeline, envp);
	if (!add_to_envp_if_not("OLDPWD", &pipeline->envp))
		exit(2);
	if (!inc_shlvl(pipeline))
		exit(2);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
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
		process_shline(symbol_matrix, pipeline);
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
