/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <aglady@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 18:41:36 by aglady            #+#    #+#             */
/*   Updated: 2020/11/12 12:23:59 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32

#endif

static int	ft_strmodif0(char **unused, char *find, char **line)
{
	char	*tmp;
	size_t	size;

	*line = ft_substr(*unused, 0, find - *unused);
	if (!(*line))
	{
		free(*unused);
		return (-1);
	}
	tmp = *unused;
	find++;
	size = ft_strlen(find) + 1;
	*unused = (char *)malloc(size * sizeof(char));
	if (!(*unused))
	{
		free(tmp);
		return (-1);
	}
	(*unused)[0] = '\0';
	ft_strcat(*unused, find);
	free(tmp);
	return (1);
}

static int	ft_strmodif1(char **unused, char **buf)
{
	char	*tmp;
	size_t	size;

	tmp = *unused;
	size = ft_strlen(*buf) + 1 + ft_strlen(tmp);
	*unused = (char *)malloc(size * sizeof(char));
	if (!(*unused))
	{
		free(tmp);
		free(*buf);
		*buf = NULL;
		return (-1);
	}
	(*unused)[0] = '\0';
	ft_strcat(*unused, tmp);
	ft_strcat(*unused, *buf);
	free(tmp);
	free(*buf);
	*buf = NULL;
	return (0);
}

static int	ft_strfinal(char **unused, char **line, char **buf)
{
	free(*buf);
	*buf = NULL;
	if (!*unused)
	{
		*line = (char *)malloc(sizeof(char));
		if (!*line)
			return (-1);
		(*line)[0] = '\0';
	}
	else
	{
		*line = ft_substr(*unused, 0, ft_strlen(*unused));
		free(*unused);
		*unused = NULL;
		if (!*line)
			return (-1);
	}
	return (0);
}

static int	ft_read(int fd, char **buf, size_t buf_size, int *size)
{
	*size = read(fd, *buf, buf_size);
	if (*size == -1)
	{
		free(*buf);
		*buf = NULL;
	}
	else
		(*buf)[*size] = '\0';
	return (*size);
}

int	get_next_line(int fd, char **line)
{
	int			size;
	char		*find;
	static char	*unused = NULL;
	char		*buf;

	if (BUFFER_SIZE < 1 || !line)
		return (-1);
	while (1)
	{
		find = ft_strchr(unused, '\n');
		if (find)
			return (ft_strmodif0(&unused, find, line));
		buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf || ft_read(fd, &buf, BUFFER_SIZE, &size) == -1)
		{
			free(unused);
			return (-1);
		}
		if (!(size))
			return (ft_strfinal(&unused, line, &buf));
		if (ft_strmodif1(&unused, &buf))
			return (-1);
	}
}
