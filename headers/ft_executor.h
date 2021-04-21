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
int			execute_builtins(t_cmds_pipeline *pipeline);
void		execute_not_builtins(t_cmds_pipeline *pipeline);
int			ft_echo(t_cmds_pipeline *pipeline);
int			ft_cd(t_cmds_pipeline *pipeline);
int			ft_pwd(t_cmds_pipeline *pipeline);
int			ft_export(t_cmds_pipeline *pipeline);
int			ft_unset(t_cmds_pipeline *pipeline);
int			ft_env(t_cmds_pipeline *pipeline);
int			ft_exit(t_cmds_pipeline *pipeline);
char		**list_to_envp(t_list *list_envp);
t_env_var	*new_env_var(char *envp_line);
t_list		*search_env(t_list *envp, const char *key);
int			insert_env(t_list *envp, char *arg);
int			invalid_key(char *key);
void		show_export(t_list *envp);
char		*get_pwd(void);

#endif
