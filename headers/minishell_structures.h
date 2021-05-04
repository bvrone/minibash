/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structures.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 18:46:38 by bvrone            #+#    #+#             */
/*   Updated: 2021/04/21 18:47:54 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTURES_H
# define MINISHELL_STRUCTURES_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_command
{
	int			argc;
	char		**argv;
	int			red_fd[2];
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
	int			tmp_fdin;
	int			tmp_fdout;
	int			last_ret_code;
	t_outf_flag	outfile_oflag;
}				t_cmds_pipeline;

int			keycmp(const char *s1, const char *s2);
void		envp_to_list(t_cmds_pipeline *pipeline, char *envp[]);
int			set_env_var(t_env_var *var, char *envp_line);
t_env_var	*find_env_var(char *key, t_list *envp);
t_env_var	*new_env_var(char *envp_line);
void		error_exit(char *target, char *msg, int ret_code);
void		put_error(char *target, char *msg);
void		clear_pipeline(t_cmds_pipeline *pipeline);
int			add_to_envp_if_not(char *key, t_list **envp);
int			inc_shlvl(t_cmds_pipeline *pipeline);

#endif
