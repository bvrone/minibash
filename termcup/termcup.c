/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 20:32:57 by aglady            #+#    #+#             */
/*   Updated: 2021/04/22 20:33:00 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcup.h"

int	read_hist_of_file(t_hist *history)
{
	int		fd;
	int		res;
	char	*line;

	errno = 0;
	fd = open("/Users/Shared/minishell_history", O_RDONLY);
	if (fd != -1)
	{
		while (1)
		{
			res = get_next_line(fd, &line);
			if (res == -1)
				error_exit("gnl", "reading error", 2);
			if (ft_strlen(line))
				hist_add(history, line);
			free(line);
			if (!res)
				break ;
		}
		close(fd);
		return (0);
	}
	return (1);
}

int	init_termcup(t_hist *history, t_termcup *ttc, t_hist_node **cur)
{
	hist_init(history);
	read_hist_of_file(history);
	if (!hist_add(history, ""))
		exit(2);
	*cur = history->last;
	tcgetattr(0, &(ttc->term));
	ttc->term.c_lflag &= ~(ECHO);
	ttc->term.c_lflag &= ~(ICANON);
	ttc->term.c_lflag &= ~(ISIG);
	tcsetattr(0, TCSANOW, &(ttc->term));
	ttc->term_name = ft_strdup("xterm-256color");
	if (!ttc->term_name)
		return (-1);
	tgetent(0, ttc->term_name);
	tputs(save_cursor, 1, ft_putchar);
	return (0);
}

void	is_up_or_down_arrow(t_hist *history, char *str, t_hist_node	**cur)
{
	if (!ft_strcmp(str, "\e[A"))
	{
		if (*cur != history->first)
			*cur = (*cur)->prev;
	}
	else
	{
		if (*cur != history->last)
			*cur = (*cur)->next;
	}
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgetstr("cd", 0), 1, ft_putchar);
	ft_putstr_fd((*cur)->data, 1);
}

int	termcup_process(t_hist *history, t_termcup *ttc, t_hist_node **cur,
					char **line)
{
	char		str[2000];
	int			k;

	while (1)
	{
		k = read(0, str, 100);
		str[k] = 0;
		if (!ft_strcmp(str, "\e[A") || !ft_strcmp(str, "\e[B"))
			is_up_or_down_arrow(history, str, cur);
		else if (!ft_strcmp(str, "\177"))
			is_backspace(cur);
		else if (!ft_strcmp(str, "\4") && !ft_strlen((*cur)->data))
		{
			write(1, "exit\n", 6);
			return (0);
		}
		else if (!ft_strcmp(str, "\3"))
			return (is_sig_int(history, ttc));
		else if (!ft_strcmp(str, "\n"))
			return (is_new_line(history, cur, line, ttc));
		else if (!(is_not_special_char(&(*cur)->data, str) + 1))
			return (-1);
	}
	return (1);
}

int	termcup(char **line)
{
	t_hist_node	*cur;
	int			res;
	t_termcup	ttc;
	t_hist		history;

	res = init_termcup(&history, &ttc, &cur);
	if (res == -1)
		return (-1);
	return (termcup_process(&history, &ttc, &cur, line));
}
