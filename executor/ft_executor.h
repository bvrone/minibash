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
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>
# include "../libft/libft.h"

typedef struct s_command
{
	int			argc;
	char		**argv;
}				t_command;

typedef struct s_env_var
{
	char		*key;
	char		*value;
	int			exp;
}				t_env_var;

typedef enum e_outf_flag
{
	rewrite,
	append
}	t_outf_flag;

typedef struct s_cmds_pipeline
{
	t_list		*cmds;
	t_list		*envp;
	char		*infile;
	char		*outfile;
	int			last_ret_code;
	t_outf_flag	outfile_oflag;
}				t_cmds_pipeline;

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
void		envp_to_list(t_cmds_pipeline *pipeline, char *envp[]);
char		**list_to_envp(t_list *list_envp);
int			set_env_var(t_env_var *var, char *envp_line);
t_env_var	*new_env_var(char *envp_line);
int			keycmp(const char *s1, const char *s2);
t_list		*search_env(t_list *envp, const char *key);
int			insert_env(t_list *envp, char *arg);
int			invalid_key(char *key);
void		show_export(t_list *envp);
char		*get_pwd(void);

#endif
