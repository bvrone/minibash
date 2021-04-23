/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:01:18 by aglady            #+#    #+#             */
/*   Updated: 2021/04/20 17:01:20 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCUP_H
# define TERMCUP_H
# include "ft_executor.h"
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>

typedef struct s_hist_node
{
	char				*data;
	struct s_hist_node	*prev;
	struct s_hist_node	*next;
}	t_hist_node;

typedef struct s_hist
{
	struct s_hist_node	*first;
	struct s_hist_node	*last;
	int					size;
}				t_hist;

typedef struct s_termcup
{
	struct termios	term;
	char			*term_name;
}			t_termcup;

void		hist_init(t_hist *history);
t_hist_node	*hist_new(char *data);
int			hist_add(t_hist *history, char *data);
void		hist_clear(t_hist *history);
int			hist_append(char *tmp);
int			termcup(char **line);
int			ft_putchar(int c);
void		is_backspace(t_hist_node **cur);
int			is_new_line(t_hist *history, t_hist_node **cur, char **line,
				t_termcup *ttc);
int			is_not_special_char(char **input, char *str);

#endif
