/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_quotes_dirty_hack.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvrone <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 20:43:35 by bvrone            #+#    #+#             */
/*   Updated: 2021/05/05 20:43:37 by bvrone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_quotes_in_line(char *line, size_t i, size_t end)
{
	while (i < end)
	{
		if (line[i] == '"' || line[i] == '\'')
			return (1);
		++i;
	}
	return (0);
}
