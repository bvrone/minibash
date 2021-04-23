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

int	init_termcup(t_hist *history, t_termcup *ttc, t_hist_node **cur)
{
	*cur = history->last;
	ttc->hist_line = NULL;
	ttc->input = ft_strdup("");
	if (!ttc->input)
		return (-1);
	tcgetattr(0, &(ttc->term));
	ttc->term.c_lflag &= ~(ECHO);
	ttc->term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &(ttc->term));
	ttc->term_name = ft_strdup("xterm-256color");
	if (!ttc->term_name)
		return (-1);
	tgetent(0, ttc->term_name);
	tputs(save_cursor, 1, ft_putchar);
	return (0);
}

int	is_up_or_down_arrow(t_hist *history, char *str, t_termcup *ttc,
						t_hist_node	**cur)
{
	int	res;

	if (!ft_strcmp(str, "\e[A"))
	{
		res = is_up_arrow(history, &(ttc->hist_line), cur);
		if (res == -1)
			return (-1);
	}
	else if (!ft_strcmp(str, "\e[B"))
	{
		res = is_down_arrow(history, ttc->input, &(ttc->hist_line), cur);
		if (res == -1)
			return (-1);
	}
	return (0);
}

int	is_sig_or_new_line(t_hist *history, char *str, t_termcup *ttc,
					char **line)
{
	if (!ft_strcmp(str, "\4") && !ft_strlen(ttc->input))
	{
		write(1, "exit\n", 6);
		return (0);
	}
	else
	{
		tcgetattr(0, &(ttc->term));
		ttc->term.c_lflag |= (ECHO);
		ttc->term.c_lflag |= (ICANON);
		tcsetattr(0, TCSANOW, &(ttc->term));
		return (is_new_line(history, line, &(ttc->input), &(ttc->hist_line)));
	}
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
		{
			if (!(is_up_or_down_arrow(history, str, ttc, cur) + 1))
				return (-1);
		}
		else if ((!ft_strcmp(str, "\4") && !ft_strlen(ttc->input))
			|| !ft_strcmp(str, "\n"))
			return (is_sig_or_new_line(history, str, ttc, line));
		else if (ft_strcmp(str, "\e[C") && ft_strcmp(str, "\e[D")
			&& ft_strcmp(str, "\4"))
		{
			if (!(is_not_special_char(&(ttc->input), str) + 1))
				return (-1);
		}
	}
	return (1);
}

int	termcup(t_hist *history, char **line)
{
	t_hist_node	*cur;
	int			res;
	t_termcup	ttc;

	res = init_termcup(history, &ttc, &cur);
	if (res == -1)
		return (-1);
	return (termcup_process(history, &ttc, &cur, line));
}
