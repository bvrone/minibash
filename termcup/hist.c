/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:09:04 by aglady            #+#    #+#             */
/*   Updated: 2021/04/20 17:09:05 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcup.h"

void	hist_init(t_hist *history)
{
	if (!history)
		return ;
	history->first = NULL;
	history->last = NULL;
	history->size = 0;
}

t_hist_node	*hist_new(char *data)
{
	t_hist_node	*new_elem;

	new_elem = (t_hist_node *)malloc(sizeof(*new_elem));
	if (!new_elem)
		return (NULL);
	new_elem->data = ft_strdup(data);
	if (!new_elem->data)
		return (NULL);
	new_elem->prev = NULL;
	new_elem->next = NULL;
	return (new_elem);
}

int	hist_add(t_hist *history, char *data)
{
	t_hist_node	*new_elem;

	new_elem = hist_new(data);
	if (!new_elem)
		return (0);
	history->size++;
	if (!history->first)
	{
		history->first = new_elem;
		history->last = new_elem;
		return (1);
	}
	new_elem->prev = history->last;
	history->last->next = new_elem;
	history->last = new_elem;
	return (1);
}

void	hist_clear(t_hist *history)
{
	t_hist_node	*tmp;

	while (history->first)
	{
		tmp = history->first;
		history->first = history->first->next;
		if (tmp->data)
			free(tmp->data);
		free(tmp);
	}
	history->last = NULL;
	history->size = 0;
}

int	hist_append(char *tmp)
{
	int	fd;

	if (!ft_strlen(tmp))
		return (0);
	errno = 0;
	fd = open("/Users/Shared/minishell_history", O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd != -1)
	{
		ft_putendl_fd(tmp, fd);
		close(fd);
		return (0);
	}
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}
