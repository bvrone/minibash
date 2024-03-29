/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 01:24:19 by bvrone            #+#    #+#             */
/*   Updated: 2021/04/07 01:24:57 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define SPACES					" \n\t\r"
# define CMD_DELIMITS			";|"
# define WRONG_FILENAME_SYMBOLS	"|;#&<>\\"

# include "minishell_structures.h"

typedef enum e_fd_type
{
	in,
	out
}	t_fd_type;

typedef struct s_start_end
{
	size_t	start;
	size_t	end;
}			t_start_end;

size_t		handle_dollar(char **matrix, size_t *i, t_cmds_pipeline	*pipeline);
size_t		handle_quotes(char **matrix, size_t *i, t_cmds_pipeline *pipeline);
size_t		handle_dquotes(char **matrix, size_t *i,
				t_cmds_pipeline *pipeline);
int			handle_redirect(char **matrix, size_t *i, size_t cmd_end,
				t_cmds_pipeline *pipeline);
char		**split_line_to_matrix(char *line);
int			split_to_lexemes(char **matrix);
char		*get_key_from_m(char **matrix, size_t key_start, size_t key_len);
size_t		env_value_to_m(char **matrix, size_t *dollar_i,
				t_env_var *env_var);
void		*clear_matrix(char **matrix, size_t count);
int			check_filename_syntax(char **matrix, size_t *i);
int			check_redir_syntax(char **symbol_matrix, size_t *i);
int			check_shielding_syntax(char **matrix, size_t *i);
void		comment_start(char **symbol_matrix, size_t *i);
int			parse_pipeline(char **symbol_matrix, size_t *cur_i,
				t_cmds_pipeline *pipeline, char *line);
void		skip_spaces(char **symbol_matrix, size_t *i);
int			skip_double_quotes(char **symbol_matrix, size_t *i);
size_t		skip_apostrophe(char **symbol_matrix, size_t *i);
size_t		skip_quotes(char **symbol_matrix, size_t *i);
size_t		set_values_in_lexemes(char **matrix, size_t i, size_t end,
				t_cmds_pipeline *pipeline);
int			get_argc(char **matrix, size_t i, size_t cmd_end, char *line);
char		**get_argv(char **matrix, size_t *cmd_i, size_t cmd_end,
				size_t argc);
void		symbol_shielding(char **symbol_matrix, size_t *i);
int			check_seprs_syntax(char **matrix);
int			is_quotes_in_line(char *line, size_t i, size_t end);

#endif