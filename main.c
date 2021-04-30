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

void	free_cmd(void *cmd)
{
	ft_split_clear(((t_command *)cmd)->argv);
	free(cmd);
	cmd = NULL;
}

void	clear_pipeline(t_cmds_pipeline *pipeline)
{
	ft_lstclear(&pipeline->cmds, &free_cmd);
	pipeline->fdin = -1;
	pipeline->fdout = -1;
}
void	process_shline(char **symbol_matrix, t_cmds_pipeline *pipeline)
{
	size_t	pipeline_i;

	pipeline_i = 0;
	if (!split_to_lexemes(symbol_matrix) || !check_seprs_syntax(symbol_matrix))
	{
		ft_putendl_fd("syntax error", 2);
		clear_pipeline(pipeline);
		return;
	}
	while (symbol_matrix[pipeline_i])
	{
		if (parse_pipeline(symbol_matrix, &pipeline_i, pipeline) == -1)
			return (clear_pipeline(pipeline));
		ft_executor(pipeline);
		clear_pipeline(pipeline);
	}
}

int		add_to_envp_if_not(char *key, t_list **envp)
{
	t_env_var	*env_var;
	t_list		*new_lst;

	if (!find_env_var(key, *envp))
	{
		env_var = new_env_var(key);
		if (!env_var)
			return (0);//malloc error
		new_lst = ft_lstnew(env_var);
		if (!new_lst)
			return (0);//malloc error
		ft_lstadd_front(envp,new_lst);
	}
	return (1);
}

int		inc_shlvl(t_cmds_pipeline *pipeline)
{
	t_env_var	*shlvl_var;
	int			lvl;

	if (!add_to_envp_if_not("SHLVL=", &pipeline->envp))
		return (0);
	shlvl_var = find_env_var("SHLVL", pipeline->envp);
	if (shlvl_var->value)
	{
		lvl = ft_atoi(shlvl_var->value);
		lvl++;
		free(shlvl_var->value);
		shlvl_var->value = ft_itoa(lvl);
	}
	else 
		shlvl_var->value = ft_strdup("1");
	if (!shlvl_var->value)
		return(0);
	return (1);
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

int		main(int argc, char *argv[], char *envp[])
{
	int				res;
	char			*line;
	char			**symbol_matrix;
	t_cmds_pipeline	pipeline;

	(void)argc;
	(void)argv;
	init_vars(&pipeline, envp);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while (1)
	{
		ft_putstr_fd("minishell$ ", 1);
		res = termcup(&line);
		if (!res)
			exit(0);
		if (res == 2)
			continue ;
		if(res < 0)
			exit(2);
		symbol_matrix = split_line_to_matrix(line);
		if (!symbol_matrix)
			exit(1);
		process_shline(symbol_matrix, &pipeline);
		free(line);
		ft_split_clear(symbol_matrix);
	}
	return (0);
}
