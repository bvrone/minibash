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

void	is_backspace(t_hist_node **cur)
{
	if (ft_strlen((*cur)->data))
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(tgetstr("cd", 0), 1, ft_putchar);
		(*cur)->data[ft_strlen((*cur)->data) - 1] = 0;
		ft_putstr_fd((*cur)->data, 1);
	}
}

int	is_sig_int(t_hist *history, t_termcup *ttc)
{
	tcgetattr(0, &(ttc->term));
	ttc->term.c_lflag |= (ECHO);
	ttc->term.c_lflag |= (ICANON);
	ttc->term.c_lflag |= (ISIG);
	tcsetattr(0, TCSANOW, &(ttc->term));
	write(1, "\n", 1);
	hist_clear(history);
	free(ttc->term_name);
	return (2);
}

int	is_new_line(t_hist *history, t_hist_node **cur, char **line,
			t_termcup *ttc)
{
	tcgetattr(0, &(ttc->term));
	ttc->term.c_lflag |= (ECHO);
	ttc->term.c_lflag |= (ICANON);
	ttc->term.c_lflag |= (ISIG);
	tcsetattr(0, TCSANOW, &(ttc->term));
	*line = ft_strdup((*cur)->data);
	if (!(*line) || hist_append((*cur)->data))
		return (-1);
	write(1, "\n", 1);
	hist_clear(history);
	free(ttc->term_name);
	return (1);
}

int	is_not_special_char(char **input, char *str)
{
	char	*tmp;

	if (ft_strcmp(str, "\e[C") && ft_strcmp(str, "\e[D")
		&& ft_strcmp(str, "\4") && ft_strcmp(str, "\034"))
	{
		tmp = ft_strjoin(*input, str);
		if (!tmp)
			return (-1);
		free(*input);
		*input = ft_strdup(tmp);
		if (!(*input))
			return (-1);
		free(tmp);
		ft_putstr_fd(str, 1);
	}
	return (0);
}
