/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:09:33 by aglady            #+#    #+#             */
/*   Updated: 2021/04/06 17:09:35 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXECUTOR_H
# define FT_EXECUTOR_H

# include <sys/types.h>
# include <signal.h>
# include "minishell_structures.h"

int			ft_executor(t_cmds_pipeline *pipeline);
int			execute_builtins(t_cmds_pipeline *pipeline, t_list *cmds);
void		execute_not_builtins(t_cmds_pipeline *pipeline, t_list *cmds);
int			ft_echo(t_cmds_pipeline *pipeline, t_list *cmds);
int			ft_cd(t_cmds_pipeline *pipeline, t_list *cmds);
int			ft_pwd(t_cmds_pipeline *pipeline, t_list *cmds);
int			ft_export(t_cmds_pipeline *pipeline, t_list *cmds);
int			ft_unset(t_cmds_pipeline *pipeline, t_list *cmds);
int			ft_env(t_cmds_pipeline *pipeline, t_list *cmds);
int			ft_exit(t_cmds_pipeline *pipeline, t_list *cmds);
char		**list_to_envp(t_list *list_envp);
t_env_var	*new_env_var(char *envp_line);
t_list		*search_env(t_list *envp, const char *key);
int			insert_env(t_list *envp, char *arg);
int			invalid_key(char *key);
void		show_export(t_list *envp);
char		*get_pwd(void);
int			exec_pipeline(t_cmds_pipeline *pipeline, int *tmp);
void		exec_one_not_builtins(t_cmds_pipeline *pipeline, t_list *cmds);
int			init_pipe_fd(int ***pipe_fd, size_t n);
void		init_in_out(t_cmds_pipeline *pipeline, int *tmp,
				size_t n, int *in_out);
void		set_in_out(t_cmds_pipeline *pipeline, int *in_out,
				int **pipe_fd, size_t i);
void		close_pipe_fd(t_cmds_pipeline *pipeline, int **pipe_fd,
				size_t n, size_t i);
int			get_child_retcode(int status);

#endif
