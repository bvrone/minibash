/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_termcup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 23:32:08 by aglady            #+#    #+#             */
/*   Updated: 2021/04/22 23:32:16 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcup.h"

int	ft_putchar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

int	is_up_arrow(t_hist *history, char **hist_line, t_hist_node	**cur)
{
	if (!history->first)
		return (0);
	if (*hist_line)
	{
		if (*cur != history->first)
			*cur = (*cur)->prev;
		free(*hist_line);
		*hist_line = ft_strdup((*cur)->data);
		if (!(*hist_line))
			return (-1);
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("cd", 0), 1, ft_putchar);
		ft_putstr_fd((*cur)->data, 1);
	}
	else
	{
		*hist_line = ft_strdup((*cur)->data);
		if (!(*hist_line))
			return (-1);
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("cd", 0), 1, ft_putchar);
		ft_putstr_fd((*cur)->data, 1);
	}
	return (0);
}

int	is_down_arrow(t_hist *history, char *input, char **hist_line,
				t_hist_node	**cur)
{
	if (!history->first)
		return (0);
	if (*hist_line)
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("cd", 0), 1, ft_putchar);
		if (*cur != history->last)
		{
			*cur = (*cur)->next;
			free(*hist_line);
			*hist_line = ft_strdup((*cur)->data);
			if (!(*hist_line))
				return (-1);
			ft_putstr_fd((*cur)->data, 1);
		}
		else
		{
			free(*hist_line);
			*hist_line = NULL;
			ft_putstr_fd(input, 1);
		}
	}
	return (0);
}

int	is_new_line(t_hist *history, char **line, char **input,
				char **hist_line)
{
	if (!(*hist_line))
	{
		*line = ft_strdup(*input);
		if (!(*line))
			return (-1);
		hist_add(history, *input);
	}
	else
	{
		*line = ft_strdup(*hist_line);
		if (!(*line))
			return (-1);
		hist_add(history, *hist_line);
	}
	free(*input);
	free(*hist_line);
	write(1, "\n", 1);
	return (1);
}

int	is_not_special_char(char **input, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(*input, str);
	if (!tmp)
		return (-1);
	free(*input);
	*input = ft_strdup(tmp);
	if (!(*input))
		return (-1);
	free(tmp);
	ft_putstr_fd(str, 1);
	return (0);
}
