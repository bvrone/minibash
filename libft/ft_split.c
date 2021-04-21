/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:21:13 by aglady            #+#    #+#             */
/*   Updated: 2020/11/04 16:21:10 by aglady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *str, char c)
{
	int		i;
	int		count;

	if (str[0] == c)
		count = 0;
	else
		count = 1;
	i = 1;
	while (str[i])
	{
		if (str[i - 1] == c && str[i] != c)
			count++;
		i++;
	}
	return (count);
}

static int	ft_len_word(char const *str, char c)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	ft_copy_word(const char *s, char c, int *i, char **res)
{
	int		len;
	int		j;

	len = ft_len_word(s + (*i), c);
	*res = (char *)malloc((len + 1) * sizeof(char));
	if (res)
	{
		j = 0;
		while (j < len)
		{
			(*res)[j] = s[*i];
			(*i)++;
			j++;
		}
		(*res)[j] = '\0';
		(*i)--;
		return (1);
	}
	return (0);
}

char	**ft_split_clear(char **res)
{
	int		k;

	k = 0;
	while (res[k])
	{
		free(res[k]);
		k++;
	}
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		k;

	res = NULL;
	if (s)
	{
		res = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
		if (res)
		{
			i = 0;
			k = -1;
			while (s[i])
			{
				if (s[i] != c)
					if (!(ft_copy_word(s, c, &i, &res[++k])))
						return (ft_split_clear(res));
				i++;
			}
			res[++k] = 0;
		}
	}
	return (res);
}
