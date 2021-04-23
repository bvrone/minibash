/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 17:41:50 by bvrone            #+#    #+#             */
/*   Updated: 2021/04/21 17:42:08 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	get_red_end(char **matrix, size_t i, size_t cmd_end)
{
	while (i < cmd_end)
	{
		if (matrix[i][0] == '\\')
			i++;
		else if (matrix[i][0] == '\'' || matrix[i][0] == '"')
			skip_quotes(matrix, &i);
		else if (matrix[i][0] == -1 || matrix[i][0] == '<' || matrix[i][0] == '>')
			break;
		i++;
	}
	return (i);
}

size_t	get_filename_len(char **matrix, size_t i, size_t red_end,
							t_cmds_pipeline *pipeline)
{
	size_t	flname_len;
	size_t	res;

	flname_len = 0;
	while (i < red_end)
	{
		flname_len += ft_strlen(matrix[i]);
		i++;
	}
	return (flname_len);
}

char	*get_filename(char **matrix, size_t *red_i, size_t cmd_end,
			t_cmds_pipeline	*pipeline)
{
	char	*file_name;
	size_t	flname_len;
	size_t	red_end;
	size_t	i;

	matrix[*red_i][0] = -1;
	while (matrix[*red_i][0] == -1)
		*red_i += 1;
	red_end = get_red_end(matrix, *red_i, cmd_end);
	if (!set_values_in_lexemes(matrix, *red_i, red_end, pipeline))
		return (NULL);
	flname_len = get_filename_len(matrix, *red_i, red_end, pipeline);
	file_name = malloc(flname_len + 1);
	if (!file_name)
		return (NULL);
	i = 0;
	while (*red_i < red_end)
	{
		i += ft_strlcpy(file_name + i, matrix[*red_i], flname_len + 1 - i);
		matrix[*red_i][0] = 0;
		*red_i += 1;
	}
	*red_i -= 1;
	return (file_name);
}

int		set_fd(char *filename, t_cmds_pipeline *pipeline, t_fd_type fd_type)
{
	int fd;

	errno = 0;
	if (fd_type == in)
	{
		if (pipeline->fdin != -1)
			close(pipeline->fdin);
		fd = open(pipeline->infile, O_RDONLY);
		pipeline->fdin = fd;
	}
	else
	{
		if (pipeline->fdout != -1)
			close(pipeline->fdout);
		if (pipeline->outfile_oflag == rewrite)
			fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0655);
		else
			fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0655);
		pipeline->fdout = fd;
	}
	if (fd == -1)
		put_error(filename, strerror(errno));
	return (fd);
}

int		handle_redirect(char **matrix, size_t *i, size_t cmd_end,
							t_cmds_pipeline *pipeline)
{
	char		*file_name;
	t_fd_type	fd_type;

	if (matrix[*i][0] == '<')
		fd_type = in;
	else if (matrix[*i][0] == '>')
	{
		if (matrix[*i + 1] && matrix[*i + 1][0] == '>')
		{
			matrix[*i][0] = -1;
			*i += 1;
			pipeline->outfile_oflag = append;
		}
		else
			pipeline->outfile_oflag = rewrite;
		fd_type = out;
	}
	file_name = get_filename(matrix, i, cmd_end, pipeline);
	if (!file_name)
		error_exit("Malloc", "memory allocation failed", 2);
	return (set_fd(file_name, pipeline, fd_type));
}